#include <Servo.h>


class Tiempo{
            private:
                    byte activo;//Estado del timer run/stop
                    byte estado;//Estado del Led True/False 
                    long preTime;//Pre carga de tiempo del timer       
                    long espera;// Intervalo de tiempo del timer        
            public:
            Tiempo::Tiempo( byte, long) ;// Constructor requiere actividad e intervalo como datos         
            byte Play();//Funcion persistente en el tiempo
            void Pause();//Detener timer
            void Run();//Activar Timer
            void setEspera(long);// Asignar tiempo de intervalo
            long getEspera(); // Obener tiempo de intervalo
   } ;
// ----------------------------------------
    Tiempo::Tiempo(byte actividad,long esperaconfigurable ){
     
       espera=esperaconfigurable;
       estado=false;
       activo=actividad;
       preTime=0;
    }
 
   byte Tiempo::Play()
   { if(activo==true){
      unsigned long realTime = millis();
       if(realTime - preTime > espera) {
                                       preTime = realTime;   
                                       if (estado == false)
                                           estado = true;
                                       else
                                       estado = false;
       return estado;
       }
       } 
       }
    
    void Tiempo::Pause(){ activo=false;}
    void Tiempo::Run(){ activo=true;}
    long Tiempo::getEspera(){ return espera;}
    void Tiempo::setEspera(long dato ){ espera=dato; }
    
     
class ledTime
   {  private:
         int Puerto ;// Pin Ardunio Digital a Configurar
         byte activo;//Estado del timer run/stop
         byte estado;//Estado del Led True/False 
         long preTime;//Pre carga de tiempo del timer       
         long espera;// Intervalo de tiempo del timer          


      public:
         ledTime( int, long) ;// Constructor requiere puerto e intervalo como datos         
         void ledPlay();//Funcion persistente en el tiempo
         void ledPause();//Detener timer
         void ledRun();//Activar Timer
         void setEspera(long);// Asignar tiempo de intervalo
         long getEspera(); // Obener tiempo de intervalo
   } ;
// ----------------------------------------
    ledTime::ledTime(int puertoconfiguracion,long esperaconfigurable ){
       Puerto=puertoconfiguracion;
       espera=esperaconfigurable;
       pinMode(Puerto,OUTPUT);
       estado=false;
       activo=true;
       preTime=0;
    }
 
   void ledTime::ledPlay()
   { if(activo==true){
      unsigned long realTime = millis();
       if(realTime - preTime > espera) {
                                       preTime = realTime;   
                                       if (estado == false)
                                           estado = true;
                                       else
                                       estado = false;
       digitalWrite(Puerto, estado);
       }
       } 
       }
    
    void ledTime::ledPause(){ activo=false;}
    void ledTime::ledRun(){ activo=true;}
    long ledTime::getEspera(){ return espera;}
    void ledTime::setEspera(long dato ){ espera=dato; }
    
     
/**************************************************************************************************************************************************************/
class Radar{
            private:
                    Servo motor;
                    byte giro;
                    long intervalo;
                    byte pin;
                    long preTime;//Pre carga de tiempo del timer       
                    byte activo;
                    byte angulo;                          
            public:
                    Radar(byte,long,byte);
                    void Radar::play();
                    void Radar::Pause();
                    void Radar::Run();
                    void Radar::pausa(long);
                    byte Radar::pos();
                    byte Radar::giros(byte); 
  };
  Radar::Radar(byte puerto,long pausa, byte info){
       pin=puerto;
       intervalo=pausa;
       giro=info;
       if(giro==true){angulo=0;}else{ angulo=180;}
       motor.attach(pin);
       motor.write(angulo);
       //Serial.begin(9600);
       //Serial.println("Radar : ON ");
       //delay(100);
       activo=true;
       preTime=millis(); 
    
    } 
  void Radar::play(){
    
    if(activo==true){
       unsigned long realTime = millis();
      if(realTime - preTime > intervalo) {
                                       preTime = realTime;   
                                       if (giro == true){ if(angulo<180){ angulo=angulo+10;} else {giro = false;}motor.write(angulo);  }
                                       else{              if(angulo > 0){ angulo=angulo-10;} else {giro = true;} motor.write(angulo);  }
                                       
                                       //Serial.print(angulo);
                                       //Serial.print("  < Angulo : Giro > ");
                                       //Serial.println(giro);     
                                          }
                    } 
       }
    
    
    void Radar::Pause(){ activo=false;}
    void Radar::Run(){ activo=true;}
    void Radar::pausa(long dato ){ intervalo=dato;}
    byte Radar::pos(){return angulo;}   
    byte Radar::giros(byte info){ angulo=180;
                                  motor.write(angulo);       
                                  giro=false;
                                             
                                     
      } 
  
  
     

/*************************************************************************************************************************************************************/

ledTime ledrojo(2,10);
ledTime ledp(13,1000);
Radar sistema1(9,20,true);
Radar sistema2(3,200,false);
Tiempo timer1(true,1000);
Tiempo timer2(true,500);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4,OUTPUT);
}

void loop() {
  byte marca=false;
  // put your main code here, to run repeatedly:
  ledrojo.ledPlay();
  ledp.ledPlay();
  sistema1.play();
  sistema2.play();
  
 
   if(timer1.Play()==true){  Serial.print("Angulo 1: ");
                           Serial.println(sistema1.pos()); }
   if(timer2.Play()==true){  Serial.print("Angulo 2: ");
                           Serial.println(sistema2.pos()); }
                            
  
}
