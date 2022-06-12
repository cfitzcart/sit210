/* SIT210 Prototype Project, T1 2022
* Remote Work Helper
* C. Fitzgerald-Carter
* Sits on a worker's desk and measures their activity sending notification reminder
* to take a break or to get back to work
* also measures ambient light and check it's appropriate for reading/working with a computer
*\



// This #include statement was automatically added by the Particle IDE.
#include <BH1750.h>


BH1750 sensor(0x23, Wire);

int PIR = D5;
String pirReading = "0";

int timeWorking = 0; //stores continuous time spent working
int timeNotWorking = 0; //stores continuous time not spent working
int count2Min = 0; 
int activity2min = 0; //stores sum of motion sensor output to determine average activity

int alert1 = 0; // flag indicates if alert has been triggered
int alert2 = 0; // flag indicates if alert has been triggered
int alert3 = 0; // flag indicates if alert has been triggered
int alert4 = 0;  // flag indicates if alert has been triggered

int prevSufficientLight = 1; //tracks when room lighting status changes


void setup() {
    

   
    sensor.begin();  // initialise light sensor
    sensor.set_sensor_mode(BH1750::forced_mode_high_res2);
    
    pinMode(PIR, INPUT); //initialise motion sensor
    
    Particle.variable("alert1", &alert1, INT); //register cloud variable for IFTTT
    Particle.variable("alert2", &alert2, INT); //register cloud variable for IFTTT   
    Particle.variable("alert3", &alert3, INT); //register cloud variable for IFTTT
    Particle.variable("alert4", &alert4, INT); //register cloud variable for IFTTT
    

}

void loop() {
    
    // 5 sec delay between measurements.
	delay(5000);
	
    //resert alert flags
    alert1 = 0; 
    alert2 = 0; 
    alert3 = 0; 
    alert4 = 0; 
	
	sensor.make_forced_measurement();

    double lx  = sensor.get_light_level(); //store output from sensor
    
    String light_level = String::format("%.1f", lx);
    checkRoomLight(lx); // evaluate if light is sufficient and trigger relevant alerts
    Particle.publish("light", light_level, PRIVATE);//send input data to console (for testing and debugging)
    
    //Read motion data and store it to variable
    if(digitalRead(PIR)==HIGH){
        //state = activeMotion;
        logActivity(1); //send current reading to log for the last 2 minutes
    }
    else if(digitalRead(PIR)==LOW){ //state = inactiveMotion;
        logActivity(0); //send current reading to log for the last 2 minutes
    }
    
    
    
}

// takes alert name as input and updates status of relevant cloud variable triggering alert
void alert(int alertName){

  String alertNum = String(alertName);
  Particle.publish("alertFlagged", alertNum, PRIVATE);
  
  if (alertName == 1){
    alert1 = 1;
  }
  else if (alertName == 2){
    alert2 = 1; 
  }
  else if (alertName == 3){ //time for a break!
    alert3 = 1; 
  }
  else if (alertName == 4){ //back to work!
    alert4 = 1;
  }
  
 
}

// tracks total continuous time spent working or taking a break
// activates relevant alerts
void breakCheck(int motion){

    if (motion == 1){ //if activity detected in last 2 minute period
       timeWorking += 2; //add additional 2 minutes to current work sprint length
       timeNotWorking = 0; //reset time spent not working
       
       String sprint = String(timeWorking);
       Particle.publish("motion", sprint, PRIVATE); //send input data to console (for testing and debugging)
  
        
      //check working 1hr or more
      if (timeWorking >= 60){
          alert(3); //trigger break time alert
       } 
    }
    else if (motion == 0){ //if no activity detected in last 2 minute period
      
      timeNotWorking += 2; //add 2 mins to current break length
      timeWorking = 0;  // reset current working sprint
      
      String sprint = String(timeNotWorking);
      String negSprint = "-"+sprint;
      Particle.publish("motion", negSprint, PRIVATE); //send input data to console (for testing and debugging)

      //check if break for more than 30 minutes
      if(timeNotWorking >= 30){
        alert(4); //trigger back to work alert
      }
    }
}

//tracks motion sensor readings for last two minute checking for any signs of activity
// passes result to breakCheck function
void logActivity(int motion){
   activity2min += motion; //add current input (1 or 0) to total sum
   count2Min ++; // increment 2 minute counter
   
  //check after 2 minutes (25 x reading every 5 mins)
  if (count2Min >= 25){
    
    if (activity2min >= 1){ //if activity detected in the last 2 mins
      breakCheck(1); 
    }
    else if (activity2min == 0){ //if activity not detected in the last 2 mins
      breakCheck(0);
    }

    count2Min = 0; //reset counter
    activity2min = 0; //reset activity record
  } 
}

// determines if room lighting is effective and activates relevant aler
void checkRoomLight(double sensorOutput){
    // if room is now well lit and was previously too dark
    if((sensorOutput > 300) && (prevSufficientLight == 0)){
        prevSufficientLight = 1; //update status memory
        alert(1); // send confirmation that lighting is now sufficient
  
    }
    // if room was previously well lit and now it's becoming too dark
    if((sensorOutput <= 300) && (prevSufficientLight == 1)){
        prevSufficientLight = 0; //update status memory
        alert(2); // send alert thatmore lighting is needed 
     
    }
}





