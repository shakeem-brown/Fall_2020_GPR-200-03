/*
   Copyright 2020 Daniel S. Buckstein

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

/*
	GPRO-Graphics1-TestConsole-main.c/.cpp
	Main entry point source file for a Windows console application.

	Modified by: ____Shakeem Brown & Andrew Barnett________
	Modified because: ___Needed to Add functions in order to make the
					  sphere._________
*/


#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>


#include "gpro/gpro-math/RTWeekend.h"
#include "gpro/gpro-math/gproVector.h"
#include "gpro/gpro-math/Vector3.h"
#include "gpro/gpro-math/Ray.h"
#include "gpro/gpro-output/Color.h"
#include "gpro/gpro-math/Hittable.h"
#include "gpro/gpro-image/Sphere.h"
#include "gpro/gpro-objects/Hittables.h"

using namespace std;

void testVector()
{
	// test array vector initializers and functions
	float3 av, bv, cv, dv;
	vec3default(av);								// -> a = (0, 0, 0)
	vec3init(bv, 1.0f, 2.0f, 3.0f);					// -> b = (1, 2, 3)
	vec3copy(dv, vec3init(cv, 4.0f, 5.0f, 6.0f));	// -> d = c = (4, 5, 6)
	vec3copy(av, dv);								// a = d			-> a = (4, 5, 6)
	vec3add(dv, bv);								// d += b			-> d = (4 + 1, 5 + 2, 6 + 3) = (5, 7, 9)
	vec3sum(dv, bv, bv);							// d = b + b		-> d = (1 + 1, 2 + 2, 3 + 3) = (2, 4, 6)
	vec3add(vec3sum(dv, cv, bv), av);				// d = c + b + a	-> d = (4 + 1 + 4, 5 + 2 + 5, 6 + 3 + 6) = (9, 12, 15)

#ifdef __cplusplus
	// test all constructors and operators
	vector_3 a, b(1.0f, 2.0f, 3.0f), c(cv), d(c);		// default; init; copy array; copy
	a = d;											// assign						-> a = (4, 5, 6)
	d += b;											// add assign					-> d = (5, 7, 9)
	d = b + b;										// sum, init, assign			-> d = (2, 4, 6)
	d = c + b + a;									// sum, init, sum, init, assign	-> d = (9, 12, 15)
#endif	// __cplusplus
}


#ifdef _cplusplus
// includes for C++
#include <fstream>
#inculde <string>
#else  // !_cplusplus
// includes for C
#endif // _cplusplus

// returns a value depending on if the sphere is hit or not
double hit_sphere(const point3& center, double radius, const ray& r)
{
	vector3 oc = r.origin() - center;
	double a = r.direction().squared_length();
	double half_b = dot(oc, r.direction());
	double c = oc.squared_length() - radius * radius;
	double discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (-half_b - sqrt(discriminant)) / a;
	}
}

// The ray's color
color ray_color(const ray& r, const hittable& world)
{
	hit_record rec; // record object
	if (world.hit(r, 0, infinity, rec)) 
	{
		return 0.5 * (rec.normal + color(1, 1, 1)); // returns this specific color
	}
	vector3 unit_direction = unit_vector(r.direction());
	double t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); // returns this specific color

}

int main(int const argc, char const* const argv[])
{
	testVector();
	ofstream object_file("Lab1.ppm");

	if (object_file) // checks if the file is open
	{
		// Image Dimensions
		const double ASPECT_RATIO = 16.0 / 9.0;
		const int IMAGE_WIDTH = 400;
		const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);

		// World Dimensions
		hittable_list world;
		world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
		world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

		// Camera Properties
		double viewport_height = 2.0;
		double viewport_width = ASPECT_RATIO * viewport_height;
		double focal_length = 1.0;

		// Camera Dimensions
		point3 origin = point3(0, 0, 0);
		vector3 horizontal = vector3(viewport_width, 0, 0);
		vector3 vertical = vector3(0, viewport_height, 0);
		point3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vector3(0, 0, focal_length); // check this

		// Render Infomation
		cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

		// Generating table values
		for (int j = IMAGE_HEIGHT - 1; j >= 0; --j)
		{
			// Actively checks while the program is running
			cerr << "\rScanlines remaining: " << j << ' ' << flush;

			// Uisng the "color", it generates each pixel and outputs its aspects to the ppm file
			for (int i = 0; i < IMAGE_WIDTH; ++i)
			{
				double u = double(i) / (static_cast<double>(IMAGE_WIDTH - 1));
				double v = double(j) / (static_cast<double>(IMAGE_HEIGHT - 1));
				ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
				color pixel_color = ray_color(r, world);
				write_color(object_file, pixel_color);
			}
		}

		// Indicates when the program is completed
		cerr << "\nDone.\n";

		// file closes
		object_file.close();
	}
	return EXIT_SUCCESS;
}



/*
#ifdef _cplusplus
	ofstream file("ppm.txt");			// open file to write
	string test = "Howdy";					// string to write
	file << test << endl;					// write string (and newline)
	file.close();								// is done, the file closes
#else // !_cplusplus
	FILE* fp = fopen("openme.txt", "w");		//open file to write
	if (fp)										// checks if the file opens
	{
		char test[] = "Howdy";					// string to write
		fprintf(fp, "%s\n", test);              // write string (and newline)
		fclose(fp);							    // is done, the file closes
	}
#endif // _cplusplus
	*/