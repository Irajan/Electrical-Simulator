#include<iostream.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>
#include<dos.h>
#include<stdio.h>

void calculate(int, int, int);
void delayPrompt(char[],unsigned);


//Make the circuitComponents Blue Print
class circuitComponents
{
  protected:
    int initialX;
    int initialY;
    int finalX;
    int finalY;
  public:
    void setLocation(int x1,int y1, int x2, int y2)
       {
	  initialX = x1;
	  initialY = y1;
	  finalX = x2;
	  finalY = y2;

	pieslice(finalX,finalY,0,360,2);  	//Circle filled with color
	pieslice(initialX,initialY,0,360,2);	//Circle filled with color
       }

};
class Resistor:public circuitComponents
{
     int resistance;
  public:
    int setValue()
    {
	delayPrompt("\nEnter the value of Resistance",45);
	cin>>resistance;
	return resistance;
    }
    void draw()
      {
	int x1,y1,x2,y2;  //Initial and final co-ordinats

	x1 = (initialX*2 + finalX)/3;
	y1 = (initialY*2 + finalY)/3;
	x2 = (initialX + finalX*2)/3;
	y2 = (initialY + finalY*2)/3;

	line(initialX,initialY,x1,y1);

	if (initialY == finalY)
	{
	   while(x1 < x2 )
	   {
	      line(x1,y1,x1+5,y1+5);
	      line(x1+5,y1+5,x1+5,y1-5);
	      line(x1+5,y1-5,x1+10,y1);
	      x1+= 10;
	   }

	}
	else if (initialX == finalX)
	{
	   while (y1 < y2)
	   {
	       line(x1,y1,x1+5,y1+5);
	       line(x1+5,y1+5,x1-5,y1+5);
	       line(x1-5,y1+5,x1,y1+10);
	       y1+= 10;
	   }
	}
	    line(x1,y1,finalX,finalY);
      }
};

class VoltageSource : public circuitComponents
{
    int amplitude;
    int frequency;
    public:
    int* setValue()
    {
	int *ampFrequency;  //array to store amplitude and frequencies
	delayPrompt("\nEnter voltage Source",30);
	delayPrompt("\nEnter the amplitude of source",30);
	cin>>amplitude;
	delayPrompt("\nEnter the frequency of source",30);
	cin>>frequency;
	*ampFrequency = amplitude;
	*(ampFrequency+1) = frequency;
	return ampFrequency;
    }
    void draw()
    {
	int x1,y1,x2,y2;
	
	//Section Formula to divide line 3:2 ratio
	x1 = (initialX*3 + finalX*2)/5;
	y1 = (initialY*3 + finalY*2)/5;
	x2 = (initialX*2 + finalX*3)/5;
	y2 = (initialY*2 + finalY*3)/5;


	line(initialX,initialY,x1,y1);
	line(x2,y2,finalX,finalY);
	int centerx,centery,radius;

	centerx = (x1+x2)/2;
	centery = (y1+y2)/2;

	if (initialX == finalX)
	    radius = (y2-y1)/2;
	else if (initialY == finalY)
	    radius = (x2-x1)/2;

	circle(centerx,centery,radius);
	circle(centerx,centery,radius-3);
	setfillstyle(1,getcolor());
	floodfill(centerx-radius+2,centery,getcolor());
	double i;

	for (i=0;i<2*radius-16;i+=0.05)
	     putpixel(centerx-radius+8+i,y1 + radius/4*sin((3.14*i)/(radius-8)),WHITE);
    }
};
class Capicator : public circuitComponents
{
  int capacitance;
  public:
    int setValue()
    {
	delayPrompt("\nEnter the value of Capacitance in micro Farad ",45);
	cin>>capacitance;
	return capacitance;
    }

    void draw()
    {
	int x1,y1,x2,y2;

	//Section Formula to divide line in 4:3 ratio
	x1 = (initialX*4 + finalX*3)/7;
	y1 = (initialY*4 + finalY*3)/7;
	x2 = (initialX*3 + finalX*4)/7;
	y2 = (initialY*3 + finalY*4)/7;

	line(initialX,initialY,x1,y1);

	if (initialX == finalX)
	{
	   line(x1-10,y1,x1+10,y1);
	   line(x2-10,y2,x2+10,y2);
	}
	else if (initialY == finalY)
	{
	   line(x1,y1-10,x1,y1+10);
	   line(x2,y2-10,x2,y2+10);
	}
	line(x2,y2,finalX,finalY);
    }
};
class Wire : public circuitComponents
{
    float internalResistance;

    public:
	void draw()
	{
	   line(initialX,initialY,finalX,finalY);
	}
	float setValue()
	{
	   delayPrompt("\n Enter Internal Resistance",30);
	   cin>>internalResistance;
	   return internalResistance;
	}
	Wire()  // Initilize internal Resistance on constructor to prevent exception if not set
	{
	 internalResistance = 0.005;
	}
};
class Inductor : public circuitComponents
{
  int inductance;
  public:
    int setValue()
    {
	delayPrompt("\nEnter the value of Inductance in mili Henry",45);
	cin>>inductance;
	return inductance;
    }

    void draw()
    {
	int x1,y1,x2,y2;
	int i;
	x1 = (initialX*2 + finalX)/3;
	y1 = (initialY*2 + finalY)/3;
	x2 = (initialX + finalX*2)/3;
	y2 = (initialY + finalY*2)/3;

	line(initialX,initialY,x1,y1);
	if (initialX == finalX)
	{
	   for (i=0;i<10;i++,y1+=7)
	    {
	   if (i == 0)
	      arc(x1+5,y1,180,270+45,6);
	   else if (i==9 || y1>y2)
	      {
	       arc(x1+5,y1,45,180,6);
	       break;
	      }
	      else
	      arc(x1+5,y1,45,270+45,6);
	    }
	}
	else if (initialY == finalY)
	{
	   for (i=0;i<10;i++,x1+=7)
	     {
	      if (i == 0)
		arc(x1,y1+5,270+45,90,6);
	      else if (i == 9 || x1>x2)
	      {
		arc(x1,y1+5,90,270-45,6);
		break;
	      }
	      else
		arc(x1,y1+5,270+45,270-45,6);
	     }
	}
	line(x1,y1,finalX,finalY);
    }
};

void main()
{
   int gd = 0,gm;

   clrscr();
   initgraph(&gd,&gm,"C:\\TurboC3\\BGI");


	 Capicator C;
	 Inductor L;
	 Resistor R;
	 Wire W;
	 VoltageSource V;
   delayPrompt("\nSelect the Required Options . . .",100);


   char choice = '0';
   do
     {
	 cout<<"\n1. Pure Capacitive Circuit"<<endl;
	 cout<<"2. Pure Inductive Circuit"<<endl;
	 cout<<"3. Resistive Circuit"<<endl;
	 cout<<"4. RLC series Circuit"<<endl;
	 cout<<"5. Exit"<<endl;

	 choice = getch();
	 clrscr();	//reset cursor
	 cleardevice();	//clear screen

	switch (choice)
	{
	    case '1':
	    calculate(0,0,C.setValue());
	    C.setLocation(450,50,600,50);
	    W.setLocation(450,50,450,150);
	    V.setLocation(450,150,600,150);
	    setcolor(3);
	    W.draw();
	    W.setLocation(600,150,600,50);
	    W.draw();
	    setcolor(BLUE);
	    C.draw();
	    setcolor(GREEN);
	    V.draw();

	    break;

	    case '2':
	    calculate(0,L.setValue(),0);
	    L.setLocation(450,50,600,50);
	    W.setLocation(450,50,450,150);
	    V.setLocation(450,150,600,150);
	    setcolor(3);
	    W.draw();
	    W.setLocation(600,150,600,50);
	    W.draw();
	    setcolor(YELLOW);
	    L.draw();
		setcolor(GREEN);
	    V.draw();

	    break;

	    case '3':
	    calculate(R.setValue(),0,0);
	    R.setLocation(450,50,600,50);
	    W.setLocation(450,50,450,150);
	    V.setLocation(450,150,600,150);
	    setcolor(3);
	    W.draw();
	    W.setLocation(600,150,600,50);
	    W.draw();
	    setcolor(BROWN);
	    R.draw();
	    setcolor(GREEN);
	    V.draw();

	    break;
	    case '4':
	    calculate(R.setValue(),L.setValue(),C.setValue());
	    R.setLocation(380,50,460,50);
	    L.setLocation(460,50,540,50);
	    C.setLocation(540,50,620,50);
	    W.setLocation(380,50,380,150);
	    V.setLocation(380,150,620,150);
	    setcolor(3);
	    W.draw();
	    W.setLocation(620,150,620,50);
	    W.draw();
	    setcolor(BROWN);
	    R.draw();
	    setcolor(YELLOW);
	    L.draw();
	    setcolor(BLUE);
	    C.draw();
	    setcolor(GREEN);
	    V.draw();
	    break;

	    case '5':
	    break;
	    default :
	    delayPrompt("\nInvalid Choice Try Again . . . .",30);

	}
	cout<<"\n\nDo you want to continue . .(y/n)"<<endl;
	char ch = getch();
	if (ch == 'n' || ch == 'N')
	    choice = '5';
	else
	{
	 clrscr();
	 cleardevice();
	}
     }
   while(choice != '5');
}

//Delay certain mili seconds while typing message
void delayPrompt(char prompt[],unsigned time )
{
   int i = 0;
   while (prompt[i] != '\0')
   {
    cout<<prompt[i];
    if (prompt[i] != ' ' && prompt[i] != '\n')
	sound(30000);
    delay(time);
    nosound();
    delay(time);
    i++;
   }
   cout<<endl;
}
void calculate(int R,int L,int C)
{
   VoltageSource V;
   int *af;
   float i;
   af = V.setValue();

   clrscr();
   cleardevice();

   printf("R = %d%c\n",R,234);		//234 = ASCII value for Ohm sign	
   printf("L = %dmH\n",L);		
   printf("C = %d%cF\n",C,230);		//230 = ASCII value for mili sign
   float Zc = 0;
   if (C != 0)
     Zc = 1000000.0/(2*3.14*af[1]*C);

   float Zl = 2*3.14*af[1]*L*.001;
   float Z = sqrt(R*R + (Zl-Zc)*(Zl-Zc));
   float I = af[0]/Z;
   float pf = acos(R/Z)*(180/3.14);

   printf("Inductive Reactance => %.2f %c\n",Zl,234);
   printf("Capactive Reactance => %.2f %c\n",Zc,234);
   printf("Circuit Impedence => %.2f %c\n\n",Z,234);

   printf("Maximum Current => %.2f A\n\n",I);
   cout<<"Maximum Voltage across :"<<endl;
   if (R) cout<<"Resistor => "<<I*R<<" V"<<endl;
   if (Zl) cout<<"Inductor => "<<I*Zl<<" V"<<endl;
   if (Zc) cout<<"Capacitor => "<<I*Zc<<" V"<<endl;
   cout<<endl;

   printf("Phase Angle => %.2f%c\n\n",pf,248);

   if (Zc == Zl)
   {
	cout<<"Unit Power Factor"<<endl;
	cout<<"Resistive Circuit"<<endl;
   }
   else if (Zc > Zl)
   {
	cout<<"Power Factor = "<<cos(pf/180*3.14)<<" Leading"<<endl;
	cout<<"Capacitive Circuit"<<endl;
	pf = -pf;
   }
   else
   {
	cout<<"Power Factor = "<<cos(pf/180*3.14)<<" Lagging"<<endl;
	cout<<"Inductive Circuit"<<endl;
   }
  printf("I = %.2fsin(2%c%dt + %.1f)\n",I,227,af[1],pf);

  for (i=0;i<=230;i+=0.05)
  {
     putpixel(380+i,300+af[0]*sin(2*3.24*i*af[1]/(240*4)),GREEN);
     putpixel(380+i,300+I*sin(2*3.14*af[1]*i/(240*4) + pf),RED);
  }
  line(380,300,620,300);

//Standard style convention message as lower right corner
	
  setcolor(BLUE);
  outtextxy(380,getmaxy()-70,"Convention :");
  setcolor(3);
  outtextxy(390,getmaxy()-55,"Voltage");
  outtextxy(390,getmaxy()-40,"Current");


  setcolor(GREEN);
  rectangle(380,getmaxy()-55,385,getmaxy()-50);
  setfillstyle(SOLID_FILL,GREEN);
  floodfill(382,getmaxy()-53,GREEN);

  setcolor(RED);
  rectangle(380,getmaxy()-40,385,getmaxy()-35);
  setfillstyle(SOLID_FILL,RED);
  floodfill(382,getmaxy()-37,RED);


}
