// This #include statement was automatically added by the Particle IDE.
#include <BH1750.h>


BH1750 sensor(0x23, Wire);

// stores value for specific trigger
double ambientChange = 0;

// keeps track of previous status
int prevInDirectLight = 0;

void setup()
{
// initialise sensor
sensor.begin();

sensor.set_sensor_mode(BH1750::forced_mode_high_res2);

Particle.variable("ambientLightTrigger", &ambientChange, DOUBLE); //register cloud variable for IFTTT

}

void loop()
{
    
sensor.make_forced_measurement();

double lx  = sensor.get_light_level(); //store output from sensor

ambientChange = directLight(lx); //get IFTTT trigger considering output

delay(1000);
}

// determines if terrarium status has changed and passes value for correct IFTTT notification 
int directLight(double sensorOutput)
{
    // if direct light detected and terrarium was previously in the shade
    if((sensorOutput >= 32000) && (prevInDirectLight == 0)){
        //update status memory
        prevInDirectLight = 1;
        // send now in direct light notification
        return 1;
    }
    // if terrarium was in direct light but now isn't
    if((sensorOutput <= 32000) && (prevInDirectLight == 1)){
        //update status memory
        prevInDirectLight = 0;
        //send out of direct light notification
        return 2;
    }
    else return 0;
}