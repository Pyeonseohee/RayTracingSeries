#include "color.h"
#include "Ray.h"
#include "vec3.h"
#include <iostream>
using namespace std;


bool hit_square(const point3 &center, double radius, const Ray &r){
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0*dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return(discriminant > 0);
}

color ray_color(const Ray &r){
    if(hit_square(point3(0, 0, -1), 0.5, r)){
        return color(1, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main(){
    //Image
    const auto aspect_ratio = 16.0/9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspect_ratio);

    //Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio*viewport_height;
    auto focal_length = 1.0;


    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    //Render
    cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; --j){
        for(int i = 0; i < image_width; ++i){
            auto u = double(i)/(image_width - 1);
            auto v = double(j)/(image_height - 1);
            Ray r(origin, lower_left_corner + u*horizontal +v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(cout, pixel_color);
        }
    }
    return 0;
}