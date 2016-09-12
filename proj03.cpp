/* 
 * Author: Wade Bowers
 *
 * Created on February 3, 2015, 10:20 AM
 */

#include<iostream>
using std::cout;
using std::endl;
using std::cin;
#include<cmath>
#include<stdexcept>
using std::runtime_error;


//updates roman coordinates
void update_coordinate_rome(double &x, double &y, double v_x, double v_y, double t) {
    x = v_x*t;
    y = ((v_y*t)-0.5*9.81*pow(t,2));
}

//updates visigoth coordinates
void update_coordinate_vis(double &x, double &y, double v_x, double v_y, double t) {
    x = x - v_x*t;
    y = ((v_y*t)-0.5*9.81*pow(t,2));   
}

//calculates and returns distance
double distance(double x1, double y1, double x2, double y2) {
    return pow((pow(x1-x2,2) + pow(y1-y2,2)),0.5);
}

//continually checks projectile distance for .01 second increments
//until the threshold is met
bool simulate(double threshold, double roman_spd, double roman_angl, double roman_x,
double vis_spd, double vis_angl, double vis_x) {
    double v_x, v_y, roman_y = 0, vis_y = 0, vis_x1 = vis_x, t = 0;
    
    //check for input errors
    if (roman_spd < 0 || vis_spd < 0) {
        throw runtime_error("Velocity must be > 0.");
    } 
    if (roman_angl < 0 || roman_angl > 360) {
        throw runtime_error("Angle must be between 0 and 360 degrees.");
    } else if (vis_angl < 0 || vis_angl > 360) {
        throw runtime_error("Angle must be between 0 and 360 degrees.");
    }
    
    //get angles in radians
    roman_angl = (roman_angl * M_PI)/180;
    vis_angl = (vis_angl * M_PI)/180;
    
    //get v_x and v_y for romans, update coord
    v_x = roman_spd*cos(roman_angl);
    v_y = roman_spd*sin(roman_angl);
 
    update_coordinate_rome(roman_x, roman_y, v_x, v_y, t);
    
    //get v_x and v_y for visigoths, update coord
    v_x = vis_spd*cos(vis_angl);
    v_y = vis_spd*sin(vis_angl);
    update_coordinate_vis(vis_x, vis_y, v_x, v_y, t);    
    
    //output the results
    cout <<"t: " << t << " roman x: " << roman_x << " y: " << roman_y;
    cout << " visigoth x: " << vis_x << " y: " << vis_y;
    cout << " distance: " << distance(roman_x, roman_y, vis_x, vis_y) << endl;    
    
    while (distance(roman_x, roman_y, vis_x, vis_y) > threshold) {
        //tick time
        t = t +.01;
        
        //get v_x and v_y for romans
        v_x = roman_spd*cos(roman_angl);
        v_y = roman_spd*sin(roman_angl);
        update_coordinate_rome(roman_x, roman_y, v_x, v_y, t);
        
        //get v_x and v_y for visigoths
        v_x = vis_spd*cos(vis_angl);
        v_y = vis_spd*sin(vis_angl);
        //reinitialize vis_x
        vis_x = vis_x1;
        update_coordinate_vis(vis_x, vis_y, v_x, v_y, t);
        
        //check if either y values have gone negative
        //return false
        if (roman_y < 0 || vis_y < 0) {
            cout << "t: " << t << " roman x: " << roman_x << " y: " << roman_y;
            cout << " visigoth x: " << vis_x << " y: " << vis_y;
            cout << " distance: " << distance(roman_x, roman_y, vis_x, vis_y) << endl;
            
            return false;
        }
        
        //check the distance versus the threshold
        //return true if within threshold
        if (distance(roman_x, roman_y, vis_x, vis_y) <= threshold) {
            cout << endl << "Collision occured at " << t << " roman x: " << roman_x << " y: " << roman_y;
            cout << " visigoth x: " << vis_x << " y: " << vis_y;
            cout << " distance: " << distance(roman_x, roman_y, vis_x, vis_y) << endl;
            return true;
        }
    
        //output the results
        cout <<"t: " << t << " roman x: " << roman_x << " y: " << roman_y;
        cout << " visigoth x: " << vis_x << " y: " << vis_y;
        cout << " distance: " << distance(roman_x, roman_y, vis_x, vis_y) << endl;
        
    }

    return 0;
    
}

// your functions all go here
// don't change the main below
// just copy it into your main program

int main(){
	double tolerance ;
	double roman_spd, roman_angl, roman_x ;
	double vis_spd, vis_angl, vis_x ;

	cout << "collision threshold: ";
	cin >> tolerance ;
	cout << "Roman catapault (speed, angle, x-position): ";
	cin >> roman_spd >> roman_angl >> roman_x;
	cout << "Visigothic catapault (speed, angle, x-position): ";
	cin >> vis_spd >> vis_angl >> vis_x;

	bool saved = simulate(tolerance, roman_spd, roman_angl, roman_x,
			      vis_spd, vis_angl, vis_x);
	if (saved)
	    cout << "Rome is defended!"<<endl;
	else
	    cout << "Rome is destroyed, the Visigoths can't be defeated !!"<<endl;
	return 0 ;
}