//Right Motor Positive-D6 and Negative-D7
//Leuft Motor Positive-D4 and Negative-D5
// Right IR on A3
// Left IR on A2
// Centre IR on A4
//Forward=0b01100000
//Right=0b10100000
//Backward=0b10010000
//Left=0b01010000
//less than threshold white and more than threshold means black
//left-500
//right-300
//centre-400
//t=225
int count =0;
double distance=0;
int tl=275;
int tr=245;
int tc=150;
String ll="Left - ";
String lr="Right- ";
String lc="Centre- ";
int leftdepth=0;
int rightdepth=0;
int centre=0;
String turn;
int main(void)
{
  Serial.begin(2000000);
  DDRD=0xFF;
  while(true)
  {
     leftdepth=getleftirdepth();
    rightdepth = getrightirdepth();
    centre=getcentre();
    linefollow(leftdepth,rightdepth,centre,tl);
  } 
}
void forward()
{
  PORTD=0b01100000;
  
}
void backward()
{
  PORTD=0b10010000;
}
void rightturn()
{
  PORTD=0b00100000;
}
void leftturn()
{
  PORTD=0b01000000;
}
void completestop()
{
  PORTD=0b00000000;
}
int getleftirdepth()
{
   ADMUX=0x42;
   ADCSRA=0xC7;
    while(ADCSRA&0x40);
    int v=ADCW;
    return v;
}
int getrightirdepth()
{
   ADMUX=0x43;
   ADCSRA=0xC7;
    while(ADCSRA&0x40);
    int y=ADCW;
    return y;
}
int getcentre()
{
   ADMUX=0x44;
   ADCSRA=0xC7;
    while(ADCSRA&0x40);
    int u=ADCW;
    return u;
}
void printdata(String p,int data)
{
  Serial.print(p);
  Serial.println(data);
}
void linefollow(int left,int right,int centre,int tl)
{
//printdata(ll,left);
//printdata(lr,right);
// printdata(lc,centre);
  if(left<tl&&right<tr&&centre>tc)
  { 
    Serial.println("Forward - Normal");
    forward();
    
  }
  else if(left>tl&&right<tr&&centre>tc)
  {
    turn="Left";
    Serial.println("Left");
    leftturn();
    _delay_ms(100); 
    while(!(right>tr))
    {
      right=getrightirdepth();
      Serial.println("Taking Left- Left and centre on black, right on white");
    }
        completestop();
    _delay_ms(75);
    while(!(centre>tc))
    {
      rightturn();
      centre=getcentre();
      Serial.println("Taking Right- Aligning");
    }
        completestop();
    _delay_ms(100);                                                                  
  }
    else if(left>tl&&right<tr&&centre<tc)
  {
    turn="Left";
    Serial.println("Left");
    leftturn();
    _delay_ms(100); 
    while(!(right>tr))
    {
      right=getrightirdepth();
      Serial.println("Taking Left- Left on black, centre and right on white");
    }
        completestop();
    _delay_ms(75);
    while(!(centre>tc))
    {
      rightturn();
      centre=getcentre();
      Serial.println("Taking Right- Aligning");
    }
        completestop();
    _delay_ms(100);                                                                
  }
  else if(left<tl&&right>tr&&centre>tc)
  {
    turn="Right";
    Serial.println("Right");
    rightturn();
    _delay_ms(100);
    while(!(left>tl))
    {
      left=getleftirdepth();
      Serial.println("Taking Right - Right and centre on black, left on white");
    }
        completestop();
    _delay_ms(75);
    while(!(centre>tc))
    {
      leftturn();
      centre=getcentre();
      Serial.println("Taking Left- Aligning");
    }
        completestop();
    _delay_ms(100);  
   }
     else if(left<tl&&right>tr&&centre<tc)
  {
    turn="Right";                                                                                     
    Serial.println("Right");
    rightturn();
    _delay_ms(100);
    while(!(left>tl))
    {
      left=getleftirdepth();
      Serial.println("Taking Right - Left and centre on white, right on back");
    }
    completestop();
    _delay_ms(75);
    while(!(centre>tc))
    {
      leftturn();
      centre=getcentre();
      Serial.println("Taking Left- Aligning");
    }
    completestop();
    _delay_ms(100);  
   }
  else if(left>tl&&right>tr&&centre>tc)
  {
    forward();
    Serial.println("Forward - All 3 on black");
  }
  else if(left<tl&&right<tr&&centre<tc)
  {
    Serial.println("All 3 on white");
    if(turn.equals("Left"))
    {
      rightturn();
      _delay_ms(50);
      turn="Left";
    }
    else if(turn.equals("Right"))
    {
      leftturn();
      _delay_ms(50);
      turn="Right";
    }
   
  else
  {
    forward();
  }
 }
}
