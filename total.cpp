// total.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <sstream>


using namespace std ; 

//level one functions
int Total_Number_Points (string s);
int Number_polygons (string s);
float Maximum_X (string s);
float Maximum_Y (string s);
float Minimum_X (string s);
float Minimum_Y (string s);


string ftostr(float num)
{
    std::stringstream ss;  
    ss << num;
    return ss.str();
}

string itostr(int num)
{
    std::stringstream ss;  
    ss << num;
    return ss.str();
}
class point
{
float x,y;

public:

void set_x(float v)
{x=v;}

float get_x()
{return x ;}

void set_y(float v)
{y=v;}

float get_y()
{return y;}

float Distance(point p)
{return sqrt(pow(x-p.x,2)+pow(y-p.y,2));}

bool inside_rect (string st)
{
    float Xmax = Maximum_X (st);
    float Xmin = Minimum_X (st);
    float Ymax = Maximum_Y (st);
    float Ymin = Minimum_Y (st);
    if ( (x > Xmax) || (x < Xmin) || (y > Ymax) ||(y < Ymin) )
    return 0;
    return 1;
}

bool inside_circle (string st)
{
    st=st.substr(1);
    float x1 = atof(st.c_str());
    st=st.substr(st.find(',')+1);
    float y1=atof(st.c_str());
    st=st.substr(st.find(')')+1);
    float r=atof(st.c_str());
    float d=sqrt(pow(x-x1,2)+pow(y-y1,2));
    if(d>r)
    return 0;
    return 1;
}

//constructors
point()
{x=0 ; y=0 ; }

point(float xv , float yv )
{ x=xv ; y=yv ; }

};

class poly
{
point p[100] ;
float Area , Peri ;
int nopoints;

public:

void set_point (point a , int i)
{p[i]=a;}

point get_point (int i)
{return p[i] ; }

void set_nopoints (int i)
{ nopoints = i; }

int get_nopoints ()
{return nopoints ;}

void set_Area (float A)
{Area = A ;}

float get_Area ()
{return Area ;}

void set_Peri (float A)
{Peri = A ;}

float get_Peri ()
{return Peri ;}

//constructor 
poly()
{ nopoints=0; }
};

//functions of level 3
bool is_inside(float x ,float y , poly Q);
bool intersecting (poly Q1 , poly Q2);

int main()
{


string operation ;
string s;
cin >> s >> operation ;

//string splitting
int n , i ,j ,k , o ,m ;
poly Q[100];
point p ;
string st,str ;
st=s ;
st=st.substr(10,s.length()-2);
st+=';' ; 

for(i=0 ; i < Number_polygons (s) ; i++)
{
    n=st.find(';');
	str=st.substr(0,n);
	o=0;
	for(k=0; k < str.length() ; k++)
	{ if (str[k] == '(')
	  o++;
	}

    Q[i].set_nopoints(o);
    
    for(j=0 ; j < Q[i].get_nopoints() ;j++)
    {
        str=str.substr(1);
        p.set_x(atof(str.c_str()));
        str=str.substr(str.find(',')+1);
        p.set_y(atof(str.c_str()));
        Q[i].set_point(p,j);
        if(j < ( Q[i].get_nopoints()-1) )
        str=str.substr(str.find('('));
    }
	if(i < ( Number_polygons(s)-1))
    st=st.substr(n+1);
    
}

//level one operations
    if (operation == "Number_Polygons")
    cout << Number_polygons(s);
    
    if (operation == "Total_Number_Points")
    cout << Total_Number_Points(s);
    
    
    if (operation == "Minimum_X")
    cout << Minimum_X(s)<<endl;
    
    if (operation == "Maximum_X")
    cout << Maximum_X(s)<<endl;
    
    if (operation == "Minimum_Y")
    cout << Minimum_Y(s)<<endl;
    
    if (operation == "Maximum_Y")
    cout << Maximum_Y(s)<<endl;
    
    if (operation == "Enclosing_Rectangle" )
    cout << "("<< Minimum_X(s)<< "," << Maximum_Y(s) << ")" <<","
         << "("<< Maximum_X(s)<< "," << Maximum_Y(s) << ")" <<","
         << "("<< Maximum_X(s)<< "," << Minimum_Y(s) << ")" <<","
         << "("<< Minimum_X(s)<< "," << Minimum_Y(s) << ")" <<endl ;
         
    if (operation == "Quit")
    return 0 ;


//getting and removing Redundant_Points
int red[100];int dx0,dx1,dy0,dy1;
n= Number_polygons (s);
point p1,p2,p3;

for(i=0 ; i<100 ; i++)
{
	red[i]=0;
}


// case repeated

for (i=0 ; i < n ; i++)
{
    for(j=0 ;  j<Q[i].get_nopoints()-red[i] ; j++)
    {   p1=Q[i].get_point(j);
	    p2=Q[i].get_point(j+1);
        if ((p1.get_x() == p2.get_x()) && (p1.get_y() == p2.get_y()))
        {
           red[i]++;
           for(k=(j+1) ; k<Q[i].get_nopoints() ; k++)
           Q[i].set_point(Q[i].get_point(k+1),k);
        }
    }
}

// case last&first
for (i=0 ; i < n ; i++)
{ p1=Q[i].get_point(0);
  k = Q[i].get_nopoints()-red[i]; 
  p2=Q[i].get_point(k-1);
  
    if ((p1.get_x() == p2.get_x()) && (p1.get_y() == p2.get_y()))
        red[i]++;
}

// case slope 

for (i=0 ; i < n ; i++)
{
    for(j=0 ;  j<(Q[i].get_nopoints()-red[i]-2) ; j++)
    {
        p1= Q[i].get_point(j);
        p2= Q[i].get_point(j+1);
        p3= Q[i].get_point(j+2);
        dx0=(p1.get_x())-(p2.get_x());
        dx1=(p2.get_x())-(p3.get_x());
        dy0=(p1.get_y())-(p2.get_y());
        dy1=(p2.get_y())-(p3.get_y());
        if ((dx0 == 0 && dx1 == 0 && dy0 != 0 && dy1 != 0) || ( (dy0*dx1)==(dy1*dx0)))
        {
            red[i]++;
           for(k=(j+1) ; k<Q[i].get_nopoints() ; k++)
           Q[i].set_point(Q[i].get_point(k+1),k);
            
        } 
    }
}

// first with (last two)check
for (i=0 ; i < n ; i++)
{
    j=Q[i].get_nopoints()-red[i]-2;
	k=Q[i].get_nopoints()-red[i]-1;
	p1 = Q[i].get_point(j);
    p2 = Q[i].get_point(k);
    p3 = Q[i].get_point(0);
    dx0=(p1.get_x())-(p2.get_x());
    dx1=(p2.get_x())-(p3.get_x());
    dy0=(p1.get_y())-(p2.get_y());
    dy1=(p2.get_y())-(p3.get_y());
    if ( (dx0 == 0 && dx1 == 0 && dy0 != 0 && dy1 != 0) ||( (dx1*dy0) == (dx0*dy1)))
        red[i]++ ;
}        
  
    
//last with (first two) check
	for (i=0 ; i < n ; i++)
{
    k=Q[i].get_nopoints()-red[i]-1;
	p1 = Q[i].get_point(k);
    p2 = Q[i].get_point(0);
    p3 = Q[i].get_point(1);
    dx0=(p1.get_x())-(p2.get_x());
    dx1=(p2.get_x())-(p3.get_x());
    dy0=(p1.get_y())-(p2.get_y());
    dy1=(p2.get_y())-(p3.get_y());
    if ( (dx0 == 0 && dx1 == 0 && dy0 != 0 && dy1 != 0) ||( (dx1*dy0) == (dx0*dy1)))
       { 
		   red[i]++ ;
		   for(k=0 ; k<Q[i].get_nopoints() ; k++)
           Q[i].set_point(Q[i].get_point(k+1),k);


	   }




}        
    int Total_Redundant_Points=0;
    for(i=0 ;i<Number_polygons (s);i++)
    {
        Total_Redundant_Points += red[i] ;
    }
    
        
        
        
        
    // level two
    if (operation == "Total_Redundant_Points")
    cout <<Total_Redundant_Points ;


float d1 ,d2 ,d3 ,d4 ,d5 ,d6 ;
float x1,y1 ;
int repeat=0;
st=="";
for(i=0 ; i <  Number_polygons(s) ; i++)
{
    Q[i].set_nopoints(Q[i].get_nopoints() - red[i] );
}
// lvl2 Polygon_Points #1
if ( operation == "Polygon_Points" )
{
cin>> n ;
for(i=0; i< Q[n-1].get_nopoints() ; i++)
{
    p1=Q[n-1].get_point(i);
    if (i !=0) cout<<",";
    cout<<"("<<p1.get_x()<<","<<p1.get_y()<<")";
}
}

// lvl2 Point_Polygons #2

if ( operation == "Point_Polygons" )
{
    cin>>str;
	st="";
    str=str.substr(1);
    x1=atof(str.c_str());
    str=str.substr(str.find(',')+1);
    y1=atof(str.c_str());
    for(i=0 ; i <  Number_polygons(s) ; i++)
    {
        for(j=0; j< Q[i].get_nopoints() ;j++)
        {
            p1 = Q[i].get_point(j);
            if(p1.get_x() == x1 && p1.get_y() == y1)
			{
             st+=itostr(i+1);
             st+=',';
			}}}
         
          
    cout<<st.substr(0,st.length()-1);
	if(st =="")cout<<"none";
	}

// lvl2 List_Polygons_Points More /Less/Equal #3


if ( operation == "List_Polygons_Points" )
{
    cin>>str;
	st="";
    if(str=="More")
    {
        cin>>n;
        for(i=0 ; i <  Number_polygons(s) ; i++)
        {
            if(Q[i].get_nopoints() > n )
            {st += itostr(i+1);
             st+=',';
             }}
    cout<<st.substr(0,st.length()-1);
	if(st =="")cout<<"none";
}
    else if(str=="Less")
    {
        cin>>n;
        for(i=0 ; i <  Number_polygons(s) ; i++)
        {
            if(Q[i].get_nopoints() < n )
            {st+= itostr(i+1);
             st+=',';
             }}
         
          
    cout<<st.substr(0,st.length()-1);
	if(st =="")cout<<"none";
}
    else if(str=="Equal")
    {
        cin>>n;
        for(i=0 ; i <  Number_polygons(s) ; i++)
        {
            if(Q[i].get_nopoints() == n )
             {st+= itostr(i+1) ;
             st+=',';
             }}
         
          
    cout<<st.substr(0,st.length()-1);
	if(st =="")cout<<"none";
}}

// lvl2 List_Points_Polygons More /Less/Equal #4

if ( operation == "List_Points_Polygons" )
{
	st="";
    cin>>str;
    if(str=="More")
    {
		int c = 0;
		char v,z;
        cin>>n;
        for(k=0 ; k <  Number_polygons(s) ; k++)
        {
            for(o=0; o< Q[k].get_nopoints() ; o++)
            { repeat=0;
                for(i=k+1 ; i <  Number_polygons(s) ; i++)
                {
                   
                    for(j=0; j< Q[i].get_nopoints() ; j++)
                    {
                        p1=Q[i].get_point(j);
                        p2=Q[k].get_point(o);
                        if(( p1.get_x() == p2.get_x() ) && (p1.get_y() == p2.get_y()))
                        {repeat++;
						break;}
                    }
                    
                
                }

                if(repeat > n)

                {            
					         if(st.length() == 0)
				             { st=st+"(";
                             st= st + ftostr(p2.get_x());
                             st=st+",";
                             st=st+ ftostr(p2.get_y());
                             st=st+")";
                             st=st+"," ;
							 continue;
			             	}
							 c=0;
					for(m=1 ; m<st.length() ; m+=6)
					{
						v=st[m];z=st[m+2];
						if ( (((int) (v)-48) == (int)( p2.get_x() ) ) && ( ((int) (z)-48) == (int)( p2.get_y() ) ) ) 
                           {
							   c=1;
			             	}
                      }


					if ( c == 0 )
						{ st=st+"(";
                             st= st + ftostr(p2.get_x());
                             st=st+",";
                             st=st+ ftostr(p2.get_y());
                             st=st+")";
                             st=st+"," ;
					}
                   }





			   }
            }
        cout<<st.substr(0,st.length()-1);
		if(st =="")cout<<"none";
    
    }
    else if(str=="Less")
    {
        cin>>n;
       for(k=0 ; k <  Number_polygons(s) ; k++)
        {
            for(o=0; o< Q[k].get_nopoints() ; o++)
            { repeat=0;
                for(i=k+1 ; i <  Number_polygons(s) ; i++)
                {
                    
                    for(j=0; j< Q[i].get_nopoints() ; j++)
                    {
                        p1=Q[i].get_point(j);
                        p2=Q[k].get_point(o);
                        if(( p1.get_x() == p2.get_x() ) && (p1.get_y() == p2.get_y()))
                        {repeat++;
						break;}
                    }
                    
                
                }
                if(repeat < n)
                {
                    st=st+"(";
                    st=st+ftostr(p2.get_x());
                    st=st+",";
                    st=st+ftostr(p2.get_y());
                    st=st+")";
                    st=st+"," ;
                }
            }
            
        }
        cout<<st.substr(0,st.length()-1);
		if(st =="")cout<<"none";
    
    }
    else if(str=="Equal")
    {
        cin>>n;
        for(k=0 ; k <  Number_polygons(s) ; k++)
        {
            for(o=0; o< Q[k].get_nopoints() ; o++)
            { repeat=0;
                for(i=k+1 ; i <  Number_polygons(s) ; i++)
                {
                    
                    for(j=0; j< Q[i].get_nopoints() ; j++)
                    {
                        p1=Q[i].get_point(j);
                        p2=Q[k].get_point(o);
                        if(( p1.get_x() == p2.get_x() ) && (p1.get_y() == p2.get_y()))
                        {repeat++;
						break;}
                    }
                    
                
                }
                if(repeat == n)
                {
                    st=st+"(";
                    st=st+ftostr(p2.get_x());
                    st=st+",";
                    st=st+ftostr(p2.get_y());
                    st=st+")";
                    st=st+"," ;
                }
            }
            
        }
        cout<<st.substr(0,st.length()-1);
		if(st =="")cout<<"none";
    
    }
}


// lvl2 Polygon_Perimeter #5

if ( operation == "Polygon_Perimeter" )
{
    cin>>n;
    float peri=0 ;
    for(i=0; i< Q[n-1].get_nopoints()-1 ; i++)
    {
    p1=Q[n-1].get_point(i);
    p2=Q[n-1].get_point(i+1);
    peri += p1.Distance(p2);
    if(i == Q[n-1].get_nopoints()-2 )
    {
         p1=Q[n-1].get_point(i+1);
         p2=Q[n-1].get_point(0);
         peri += p1.Distance(p2);
    }    
    }

    cout<<peri ;
}   


// lvl2 List_Triangles #6

if ( operation == "List_Triangles" )
{ st="";
 for(i=0 ; i <  Number_polygons(s) ; i++)
 {
     if(Q[i].get_nopoints()==3)
     {       st+=itostr(i+1);
             st+=',';
             }

     }     
    cout<<st.substr(0,st.length()-1);
	if(st =="")cout<<"none";
}



// lvl2 List_Rectangles #7

if ( operation == "List_Rectangles" )
{st="";
     for(i=0 ; i <  Number_polygons(s) ; i++)
     {
         if(Q[i].get_nopoints()==4)
         {   p1=Q[i].get_point(0);
             p2=Q[i].get_point(1);
             d1=p1.Distance(p2);
             
             p1=Q[i].get_point(1);
             p2=Q[i].get_point(2);
             d2=p1.Distance(p2);
             
             p1=Q[i].get_point(2);
             p2=Q[i].get_point(3);
             d3=p1.Distance(p2);
             
             p1=Q[i].get_point(3);
             p2=Q[i].get_point(0);
             d4=p1.Distance(p2);
             
             p1=Q[i].get_point(0);
             p2=Q[i].get_point(2);
             d5=p1.Distance(p2);
             
             p1=Q[i].get_point(1);
             p2=Q[i].get_point(3);
             d6=p1.Distance(p2);
             if(d1==d3 && d2== d4 && d5 == d6)
             {
             st+=itostr(i+1);
             st+=',';
             }
         }
     }     
    cout<<st.substr(0,st.length()-1);
	if(st =="")cout<<"none";
}
// lvl2 List_Trapezoid #8


if ( operation == "List_Trapezoid" )
{st="";
    for(i=0 ; i <  Number_polygons(s) ; i++)
     {
         if(Q[i].get_nopoints()==4)
         {  
             p1=Q[i].get_point(0);
             p2=Q[i].get_point(1);
             d1=p1.Distance(p2);
             dy0=p1.get_y()-p2.get_y() ;
             dx0=p1.get_x()-p2.get_x() ;
             
             p1=Q[i].get_point(2);
             p2=Q[i].get_point(3);
             d2=p1.Distance(p2);
             dy1=p2.get_y()-p1.get_y() ;
             dx1=p2.get_x()-p1.get_x() ;
             if( (d1 != d2) && ((dy1 * dx0) == (dy0 * dx1)))
             {
             st+=itostr(i+1);
             st+=',';
             }
         }
     }     

    cout<<st.substr(0,st.length()-1);
	if(st =="")cout<<"none";
}    


//level 3

// lvl3 Inside_Rectangle #1
if ( operation == "Inside_Rectangle" )
{
    cin>>st;
    bool alltrue=1;
    bool inside[100][100];
    for(i=0 ; i <  Number_polygons(s) ; i++)
        {
            for(j=0; j< Q[i].get_nopoints() ; j++)
            {
                p1 = Q[i].get_point(j);
                inside[i][j]=p1.inside_rect(st);
            }
        }
    str="";
    for(i=0 ; i <  Number_polygons(s) ; i++)
        {
            for(j=0; j< Q[i].get_nopoints() ; j++)
            {
                if( inside[i][j] != 1 )
                alltrue=0;
            }
            if(alltrue==1)
            {
                str+=itostr(i+1);
                str+=",";
            }
        }
    cout<<str.substr(0,str.length()-1);
	if(str =="")cout<<"none";
        
}    
// lvl3 Inside_Circle #2

if ( operation == "Inside_Circle" )
{
     cin>>st;
    bool alltrue=1;
    bool inside[100][100];
    for(i=0 ; i <  Number_polygons(s) ; i++)
        {
            for(j=0; j< Q[i].get_nopoints() ; j++)
            {
                p1 = Q[i].get_point(j);
                inside[i][j]=p1.inside_circle(st);
            }
        }
    str="";
    for(i=0 ; i <  Number_polygons(s) ; i++)
        {
            for(j=0; j< Q[i].get_nopoints() ; j++)
            {
                if( inside[i][j] != 1 )
                alltrue=0;
            }
            if(alltrue==1)
            {
                str+=itostr(i+1);
                str+=",";
            }
        }
    cout<<str.substr(0,str.length()-1);
	if(str =="")cout<<"none";
}
// lvl3 Polygon_Area #3

if ( operation == "Polygon_Area" )
{
    cin>> n ;
    float sum1 = 0 , sum2 =0 ;
for(i=0; i< Q[n-1].get_nopoints() ; i++)
{
	if( i==Q[n-1].get_nopoints()-1)
	{
     p1=Q[n-1].get_point(i);
     p2=Q[n-1].get_point(0);
	}
	else
	{
    p1=Q[n-1].get_point(i);
    p2=Q[n-1].get_point(i+1);
	}
    sum1 += (p1.get_x())*(p2.get_y());
    sum2 += (p2.get_x())*(p1.get_y());
}
cout<<(abs((sum1-sum2)/2));
}



//set areas
for(i=0 ; i <  Number_polygons(s) ; i++)
        {
        float sum1 = 0 , sum2 =0 ;
        for(j=0; j< Q[i].get_nopoints() ; j++)
        {
			if( j==Q[i].get_nopoints()-1)
	          {
               p1=Q[i].get_point(j);
               p2=Q[i].get_point(0);
	           }
	         else
	           {
                p1=Q[i].get_point(j);
                p2=Q[i].get_point(j+1);
	            }
           sum1 += (p1.get_x())*(p2.get_y());
           sum2 += (p2.get_x())*(p1.get_y());
        }
        Q[i].set_Area(abs((sum1-sum2)/2));
        }


// lvl3 Polygons_Area_Range #4

if ( operation == "Polygons_Area_Range" )
{
        cin>> st ;
        x1 = atof(st.c_str());
        st=st.substr(st.find(',')+1);
        y1=atof(st.c_str());
        float sum1 = 0 , sum2 =0 ;
    str="";
    for(i=0 ; i <  Number_polygons(s) ; i++)
        {
            if(Q[i].get_Area() > x1 && Q[i].get_Area() < y1)
            {
                str += itostr(i+1);
                str+=",";
            }
        }
    cout<<str.substr(0,str.length()-1);
	if(str =="")cout<<"none";
}
// lvl3 Polygons_Enclosing_Point #5


if ( operation == "Polygons_Enclosing_Point" )

{
    cin>>str;
    str=str.substr(1);
    x1=atof(str.c_str());
    str=str.substr(str.find(',')+1);
    y1=atof(str.c_str());
   
    j= Q[i].get_nopoints()-1 ;
 
        st="";
        for(i=0 ; i <  Number_polygons(s) ; i++)
        {
          if(is_inside(x1,y1,Q[i]))
          {
              st += itostr(i+1);
                st+=",";
          }
        }
    cout<<st.substr(0,st.length()-1);
	if(st =="")cout<<"none";
}
          


// lvl3 Is_Intersecting #6


if ( operation == "Is_Intersecting" )
{
	cin>>str;
    x1=atof(str.c_str());
    str=str.substr(str.find(',')+1);
    y1=atof(str.c_str());
    if(intersecting(Q[(int)x1-1],Q[(int)y1-1]))
	cout<<"TRUE";
	else	
cout<<"FALSE";
}

// lvl3 Intersecting_Group #7


if ( operation == "Intersecting_Group" )
{

	cin>>str;
	 j=0 ;
	for(i=0 , n= str.length() ; i<n ; i+=2)
	{
		red[j]=atoi(str.c_str());
		str=str.substr(str.find(',')+1);
		j++;
	}
   for(i=0;i<j;i++)
   {
	   for(k=i+1 ; k<j ;k++)
	   {
		   if(!(intersecting(Q[red[i]- 1] ,Q[red[k]-1])))
		   {
			   cout<<"FALSE";
			   return 0;
		   }
	   }
   }
   cout<<"TRUE" ;
}


    return 0 ;
}



//level 1 <Max_Y>
float Maximum_Y (string s)
{
    int j=0 , i ;
    string Temp="" ;
    float X[10000] ;
            for(i=0 ; i < s.length() ; i++)
               {
                  if( s[i] == ',' && s[i+1] != '(' )
                    {
                       while ( s[i] != ')' )
                             {
                              i++ ;
                              Temp += s[i] ;
                              }
                     X[j] = atof(Temp.c_str()) ;
                     j++ ;
                     Temp = "";
                     }
                }
   
    float Max = X[0] ;
    for (i=1 ;  i < Total_Number_Points(s) ; i++ )
    {
        if (X[i] > Max)
        Max=X[i] ;
    }
    return Max ;
}

//level 1 <Min_X>
float Minimum_X (string s)
{
    int j=0 , i ;
    string Temp ="" ;
    float X[10000] ;
            for(i=0 ; i < s.length() ; i++)
               {
                  if( s[i] == '(' )
                    {
                       while ( s[i] != ',' )
                             {
                              i++ ;
                              Temp += s[i] ;
                              }
                     X[j] = atof(Temp.c_str()) ;
                     j++ ;
                     Temp = "";
                     }
                }
    float Max = X[0] ;
    for (i=1 ;  i < Total_Number_Points(s) ; i++ )
    {
        if (X[i] < Max)
        Max=X[i] ;
    }
    return Max ;
}

//level 1 <Min_Y>
float Minimum_Y (string s)
{
    int j=0 , i ;
    string Temp = "" ;
    float X[10000] ;
            for(i=0 ; i < s.length() ; i++)
               {
                  if( (s[i] == ',') && (s[i+1] != '(') )
                    {
                       while ( s[i] != ')' )
                             {
                              i++ ;
                              Temp += s[i] ;
                            
                              }
                     X[j] = atof(Temp.c_str()) ;
                     j++ ;
                     Temp = "";
                     }
                }
   
    float Max = X[0] ;
    for (i=1 ;  i < Total_Number_Points(s) ; i++ )
    {
        if (X[i] < Max)
        Max=X[i] ;
    }
    return Max ;
}

//level 1 <Max_X>
        float Maximum_X (string s)
        {
         int j=0 , i ;
         string Temp="" ;
         float X[10000] ;
            for(i=0 ; i < s.length() ; i++)
               {
                  if( s[i] == '(' )
                    {
                       while ( s[i] != ',' )
                             {
                              i++ ;
                              Temp += s[i] ;
                              }
                     X[j] = atof(Temp.c_str()) ;
                     j++ ;
                     Temp = "";
                     }
                }
        float Max = X[0] ;
            for (i=1 ;  i < Total_Number_Points(s) ; i++ )
                {
                  if (X[i] > Max)
                    Max=X[i] ;
        
                }
         return Max ;
        }

//level 1 <Number_polygons>
int Number_polygons (string s)
{
    int i , sum =1 ;
   for ( i=0 ; i < s.length() ; i++ )
     {
        if(s[i]==';')
        sum += 1 ;
    }
     return sum ;
}

//level 1 <Total_Number_Points>
int Total_Number_Points (string s)
{
    int i , sum=0 ;
    for ( i=0 ; i < s.length() ; i++ )
    {
        if(s[i]=='(')
        sum += 1 ;
    }
    return sum ;
}




//enclosing point level 3 
bool is_inside(float x ,float y , poly Q)
{
point p1 , p2 ;
float A2 ;
float A1 = Q.get_Area();
float Asum = 0 ;


for(int i=0 , n = Q.get_nopoints() ; i<n ; i++ )

   {

if(i==n-1)
{   
      p1 = Q.get_point(i);
      p2 = Q.get_point(0);
}

else
{
      p1= Q.get_point(i);
      p2= Q.get_point(i+1);
	 
}
A2 =abs( ( ( ( (x) * (p1.get_y()) ) + ( (p1.get_x()) * (p2.get_y()) ) + ( (p2.get_x())*(y) ) ) - ( ( (y) * (p1.get_x()) ) + ( (p1.get_y()) * (p2.get_x()) )+(p2.get_y())*(x) ) ) /2) ;
Asum += A2 ; 

}

if ( Asum == A1 )
return 1 ;
return 0 ;


}

bool intersecting (poly Q1 , poly Q2)
{
	point p1 ;
	for(int i=0 ,n=Q1.get_nopoints() ;i<n ;i++)
	{   
		if(is_inside((Q1.get_point(i)).get_x(),(Q1.get_point(i)).get_y(),Q2))
			return 1;
	}
	for(int j=0 ,k=Q2.get_nopoints() ;j<k ;j++)
	{ p1=(Q2.get_point(j));
		if(is_inside(p1.get_x(),p1.get_y(),Q1))
			return 1;
	}
	return 0;
}

