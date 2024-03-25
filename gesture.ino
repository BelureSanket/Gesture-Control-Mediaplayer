const int trigger1 = 2; //Trigger pin of 1st Sensor
const int echo1 = 3; //Echo pin of 1st Sensor
const int trigger2 = 4; //Trigger pin of 2nd Sensor
const int echo2 = 5;//Echo pin of 2nd Sensor
long time_taken;
int dist,distance_L,distance_R;

void setup() {
Serial.begin(9600);
pinMode(trigger1, OUTPUT);
pinMode(echo1, INPUT);
pinMode(trigger2, OUTPUT);
pinMode(echo2, INPUT);
}

void calculate_distance(int trigger, int echo)
{
digitalWrite(trigger, LOW);
delayMicroseconds(2);
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);
time_taken = pulseIn(echo, HIGH);
dist= time_taken*0.034/2;
if (dist>50)
dist = 50;
}
void loop() { //infinite loopy
calculate_distance(trigger1,echo1);
distance_L =dist; //get distance of left sensor
calculate_distance(trigger2,echo2);
distance_R =dist; //get distance of right sensor
//Uncomment for debudding
Serial.print("L=");
Serial.println(distance_L);
Serial.print("R=");
Serial.println(distance_R);

if ((distance_L >30 && distance_R>30) && (distance_L <50 &&
distance_R<50))
{Serial.println("Play/Pause"); delay (500);}
calculate_distance(trigger1,echo1);
distance_L =dist;
calculate_distance(trigger2,echo2);
distance_R =dist;

if (distance_L>=10 && distance_L<=20)
{
delay(100); //Hand Hold Time
calculate_distance(trigger1,echo1);
distance_L =dist;
if (distance_L>=10 && distance_L<=20)
{
Serial.println("Left Locked");
while(distance_L<=40)
{

calculate_distance(trigger1,echo1);
distance_L =dist;
if (distance_L<10) //Hand pushed in
{Serial.println ("Vup"); delay (300);}
if (distance_L>20) //Hand pulled out
{Serial.println ("Vdown"); delay (300);}
} }
}

if (distance_R>=10 && distance_R<=20)
{
delay(100); //Hand Hold Time
calculate_distance(trigger2,echo2);
distance_R =dist;
if (distance_R>=10 && distance_R<=20)
{
Serial.println("Right Locked");
while(distance_R<=40)
{
calculate_distance(trigger2,echo2);
distance_R =dist;
if (distance_R<10) //Right hand pushed in
{Serial.println ("Rewind"); delay (300);}
if (distance_R>20) //Right hand pulled out
{Serial.println ("Forward"); delay (300);}
}
}
}
delay(200);