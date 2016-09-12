/* 
 * Author: Wade Bowers
 * netid: bowerswa
 *
 * Created on December 19, 2013, 12:43 PM
 */

#include<iostream>
using std::cin;
using std::cout;
using std::endl;
#include<cmath>

int main() {
    //initialize variables
    float line1; float line2;
    double line1x; double line1y;
    double line2x; double line2y;
    double line1vm; double line2vm;
    double dp; double pi = M_PI;
    int x = 0;
    
    cout << "Enter x and y (space separated) for point 1: ";
    
    //use a while loop to get multiple values from cin
    while (cin >> line1) {
        if (x == 0) {
            line1x = line1;
        } else if (x == 1) {
            line1y = line1;
            line1vm = sqrt(line1x * line1x + line1y * line1y);
            break;
        }
        x++;
    }
    
    //reset x
    x = 0;
    
    cout << "Enter x and y (space separated) for point 2: ";
    
    //use a while loop to get multiple values from cin
    while (cin >> line2) {
        if (x == 0) {
            line2x = line2;
        } else if (x == 1) {
            line2y = line2;
            line2vm = sqrt(line2x * line2x + line2y * line2y);
            break;
        }
        x++;
    }    
    
    
    //cout << "line1x " << line1x << endl;
    //cout << "line1y " << line1y << endl;
    
    //calculate unit vector
    cout << "Unit vector for point 1, x: " << line1x/line1vm << " y: " 
            << line1y/line1vm << endl;
    
    //cout << "line2x " << line2x << endl;
    //cout << "line2y " << line2y << endl;
    
    // calculate unit vector    
    cout << "Unit vector for point 2, x: " << line2x/line2vm << " y: " 
            << line2y/line2vm << endl;
    
    //calculate dot product
    dp = line1x * line2x + line1y * line2y;
    
    cout << "The dot product is: " << dp << endl;
    
    //initialize and set angle variables
    double angle_init = dp / (line1vm * line2vm);
    double angle_rad = acos (angle_init);
    double angle = (angle_rad * 180)/pi;
    double projected_magnitude = line1vm * angle_init;
    
    cout << "The angle between the two is: " << angle << endl;
    cout << "Projection of p1 onto p2 is, x: " 
            << projected_magnitude * (line2x/line2vm)
            << " y: " << projected_magnitude * (line2y/line2vm) << endl;
    
    return 0;
}

