/*
 *   Copyright (C) 2017 Event-driven Perception for Robotics
 *   Author: arren.glover@iit.it
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "houghAlgorithm.h"

circularHoughDetector::circularHoughDetector()
{
    radius = 0;
    perimeter = 0;
    inv_perimeter = 1.0;
    max_response = pixel{0, 0};
}

bool circularHoughDetector::initialise(double radius, double thickness, int height, int width)
{

    H.resize(width, height);
    H.zero();
    duplicate_check.resize(width, height);
    duplicate_check.zero();

    xlim = width-1;
    ylim = height-1;

    this->radius = radius;
    perimeter = radius * 2.0 * M_PI + 0.5;
    inv_perimeter = 1.0 / (radius * 2 * M_PI);

    pixel_offsets.clear();
    for(int x = -radius; x <= radius; x++) {
        for(int y = -radius; y <= radius; y++) {

            if(std::fabs(sqrt(x*x + y*y) - radius) < thickness) {
                pixel_offsets.push_back(pixel{x, y});
            }

        }
    }

    processing.lock();
    done.lock();

    return this->start();

}

void circularHoughDetector::process(std::vector<ev::AE> &q)
{
    this->q = &q;
    processing.unlock();
}

double circularHoughDetector::waittilldone()
{
    done.lock();
    double score = (double)(H(max_response.x, max_response.y)) * inv_perimeter;
    if(score > 1.0) score = 1.0;
    return score;
}

int circularHoughDetector::x()
{
    return max_response.x;
}

int circularHoughDetector::y()
{
    return max_response.y;
}

int circularHoughDetector::r()
{
    return radius;
}


void circularHoughDetector::run()
{

    while(!isStopping()) {

        processing.lock();
        if(isStopping()) return;

        H.zero();
        duplicate_check.zero();

        unsigned int events_to_proc = std::min(2*perimeter, (unsigned int)q->size());

        for(size_t i = 0; i < events_to_proc; i++) {

            if(duplicate_check((*q)[i].x, (*q)[i].y))
                continue;

            duplicate_check((*q)[i].x, (*q)[i].y) = 1;

            for(size_t j = 0; j < pixel_offsets.size(); j++) {

                int x = (*q)[i].x + pixel_offsets[j].x;
                int y = (*q)[i].y + pixel_offsets[j].y;
                if(y > ylim || y < 0 || x > xlim || x < 0) continue;


                H(x, y)++;
                if(H(x, y) > H(max_response.x, max_response.y)) {
                    max_response.x = x; max_response.y = y;
                }

            }
        }

        done.unlock();

    }
}

void circularHoughDetector::onStop()
{
    processing.unlock();
}

yarp::sig::ImageOf<yarp::sig::PixelBgr> circularHoughDetector::makeDebugImage()
{

    yarp::sig::ImageOf<yarp::sig::PixelBgr> image; image.resize(H.width(), H.height());
    image.zero();

    for(int y = 0; y < ylim; y++) {
        for(int x = 0; x < xlim; x++) {

            int value = (double)(H(x, y)) * 255.0 * inv_perimeter * 2.0;
            if(value > 255) value = 255;

            yarp::sig::PixelBgr &pixel = image(x, y);
            pixel.g = value;

        }
    }

    unsigned int events_to_proc = std::min(2*perimeter, (unsigned int)q->size());
    for(size_t i = 0; i < events_to_proc; i++) {

        yarp::sig::PixelBgr &pixel = image((*q)[i].x, (*q)[i].y);
        pixel.b = 255; pixel.g = 255; pixel.r = 255;

    }

    image(max_response.x, max_response.y) = yarp::sig::PixelBgr(0, 0, 255);


    return image;
}

