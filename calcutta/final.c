
#include<math.h>
#include<stdio.h> 
#include<stdlib.h>
#define FREQ 256
#define MAX 20
#define SIZ 512

int x,y,lmin,lmax;
float w=6.00;


   //************** IMAGE CREATION *************//

int creat_image(unsigned char im[SIZ][SIZ])
{
	FILE *f2;
	unsigned char n2[MAX];
	int i=0,j=0;
	printf("\nenter output file name :: ");
	scanf("%s",n2);
	f2=fopen(n2,"w");
	fputs("P5\n",f2);
	fprintf(f2,"%d %d\n",x,y);
	fputs("255\n",f2);
	for(i=0;i<x;i++)
	for(j=0;j<y;j++)
	fprintf(f2,"%c",im[i][j]);
	fclose(f2);
	return 0;
}


    //************* THRESHOLDING ************//

int threshold(unsigned char im[SIZ][SIZ],int loc)
{
int i,j;
for(i=0;i<x;i++)
for(j=0;j<y;j++)
if(im[i][j]<loc)
im[i][j]=0;
else
im[i][j]=255;
}

int loc_min(int d[],int lmin,int lmax)
{
	int r,i,a=999999;
	for(i=lmin+1;i<lmax-1;i++)
	{
        	if(d[i-1]>d[i] && d[i+1]>d[i] && d[i]<a)
		{	
			a=d[i];
			r=i;
		}
	}
        return r;
}


                //*****FUZZY ENTROPY LOCAL MINIMA**********//

   float fuzzy_entropy_localminima(float fuzzy[],int nof,float bfuzzy[])
  {
     int r,i,j;
 float a=999999999.999,fuzzytemp[100],bfuzzytemp[100],min,minb;

         for(i=1,j=0;i<nof;i++)
       {
         
              if(fuzzy[i-1]>fuzzy[i] && fuzzy[i+1]>fuzzy[i] && fuzzy[i]<a)
             {
                 fuzzytemp[j]=fuzzy[i];
                 bfuzzytemp[j]=bfuzzy[i];
                 j++;
            }
                   
         }

//  for(i=0;i<j;i++)
  //  printf("\n%f\t%f\n",fuzzytemp[i],bfuzzytemp[i]);


      min=fuzzytemp[0];
      r=0;
      for(i=1;i<j;i++)
      {

          if(min>fuzzytemp[i])
          {
             min=fuzzytemp[i];
             r=i;
          }
      }
       minb=bfuzzytemp[r];



  return minb;   
  }


       //****** FUZZY CORRELATION LOCAL MAXIMA*******//

float fuzzy_correlation_localmaxima(float fuzzy[],int nof,float bfuzzy[])
  {
     int r,i,j;
 float a=999999999.999,fuzzytemp[100],bfuzzytemp[100],max,maxb;

         for(i=1,j=0;i<nof;i++)
       {

              if(fuzzy[i-1]<fuzzy[i] && fuzzy[i+1]<fuzzy[i] && fuzzy[i]<a)
             {
                 fuzzytemp[j]=fuzzy[i];
                 bfuzzytemp[j]=bfuzzy[i];
                 j++;
            }

         }

  for(i=0;i<j;i++)
    printf("\n%f\t%f\n",fuzzytemp[i],bfuzzytemp[i]);


     max=fuzzytemp[0];
      r=0;
      for(i=1;i<j;i++)
      {

          if(max<fuzzytemp[i])
          {
             max=fuzzytemp[i];
             r=i;
          }
      }
       maxb=bfuzzytemp[r];



  return maxb;   
  }




             //*********** HISTOGRAM ************//
   
unsigned char histo(unsigned char im[SIZ][SIZ],int count[FREQ])
{
	int i=0,j=0;
	int b,max;
	long hist1[FREQ],y_max,y_interval;

	for(i=0;i<FREQ;i++)
	  count[i]=0;

	for(i=0;i<x;i++)
	for(j=0;j<y;j++)
          count[im[i][j]]++;

	for(i=0;i<FREQ;)
	 if(count[i]==0)
	  i++;
	 else 
	 {
		lmin=i;
		break;
	 }
	 for(j=FREQ-1;j>=0;)
	 if(count[j]==0)
	  j--;
	 else
	 {
		lmax=j;
		break;
	 }
	
       	printf("\nlmin is %d.......lmax is %d\n",lmin,lmax);

        max = count[lmin];
	for( i = lmin + 1; i <= lmax; i++)
		if(max < count[i]) max = count[i];
	y_interval = (max/8 + 1);
	y_max = (256 * max) / (8 * y_interval);
	for (i=0; i <FREQ; i++)
		hist1[i] = ((double)count[i]/(double)(max)) * y_max;
	//generate_histogram (y_interval,hist1);
}

     //*************** MODIFICATION **************//

unsigned char modify(unsigned char im[SIZ][SIZ])
{	
	int d,b,i,j,f=1;
	do
	{
	printf("\nenter choice to change ::\n1:Change Brightness\n2:Increase Contrast\n3:Both\n4:None\nyour choice :: ");
	
	scanf("%d",&d);

	switch(d)
	{
		case 1:
		
			printf("Enter shift of brightness :: ");
			scanf("%d",&b);
			if((lmin-b)>=0 || (lmax+b)<=255)
			{
				for(i=0;i<x;i++)
				for(j=0;j<y;j++)
				{
					im[i][j]=im[i][j]+b;
				}
			}
			else
			printf("\ninvalid input,original values maintained");
		
		break;
		
		case 2:
			for(i=0;i<x;i++)
			for(j=0;j<y;j++)
			im[i][j]=(im[i][j]-lmin)*255/(lmax-lmin);
		break;
		

		case 3:
			printf("Enter shift of brightness :: ");
			scanf("%d",&b);
	
			if((lmin-b)>=0 || (lmax+b)<=255)
			{
				for(i=0;i<x;i++)
				for(j=0;j<y;j++)
				{
					im[i][j]=(im[i][j]-lmin)*255/(lmax-lmin);
					im[i][j]=im[i][j]+b;
				}
			}
			else
			  printf("\ninvalid input,original values maintained");
		break;

	
		case 4:
			return 0;
	}
	printf("\nWant to change further...\n1.Yes\n2.No\n");
	scanf("%d",&f);
	}
	while(f==1);
	return 0;
}


                //************** HISTOGRAM GENERATION *****************//

int generate_histogram (long y_interval,long hist[FREQ])
	{
		int i, j = 0;
		float fy_interval;
		FILE *fpw;
		char ff[20];
		printf("Enter the output file in .ps for histogram: ");
		scanf("%s",ff);
		if ((fpw = fopen(ff,"wb")) == NULL)
		{
			printf("Output File Could not be Created !\n");
			exit(1);
		}

		fputs ("%!PS-Histogram File\n",fpw);
		fputs ("%%BoundingBox: 0 0 306 283\n",fpw);
		fputs("/Courier-Bold findfont\n14 scalefont\nsetfont\nnewpath\n",fpw);
		fprintf(fpw,"9 115 moveto\n");
		fprintf(fpw,"(Frequency)\n90 rotate\nshow\n");
		fprintf(fpw,"270 rotate\n");
		fprintf(fpw,"137 3 moveto\n");
		fprintf(fpw,"(Gray level) show\n");
		fputs("/Courier findfont\n10 scalefont\nsetfont\nnewpath\n",fpw);

		if (y_interval > 10000)
		{
			fy_interval = (float)(y_interval) / 10000.0;
			fprintf(fpw,"52 283 moveto\n");
			fprintf(fpw,"(x 10^4) show\n");
		}
		fputs("0.5 setlinewidth\n",fpw);
		for ( i = 27; i <= 283; i++)
			if ((i-27)% 32 == 0)
			{
				fprintf(fpw,"50 %d moveto 46 %d lineto stroke\n",i,i);
				fprintf(fpw,"50 %d moveto 306 %d lineto\n.8 setgray\nstroke\n0 setgray\n",i,i);
				fprintf(fpw,"8 %d moveto\n",i-6);
				if (y_interval >= 10000)
					fprintf(fpw,"(%6.2f) show\n",(j++ * fy_interval));
				else
					fprintf(fpw,"(%6ld) show\n",(j++ * y_interval));
			}

		for (i=0, j=50; i <= 256; i++, j++)
		{
			if (i% 32 == 0)
			{
				fprintf(fpw,"%d 27 moveto %d 23 lineto stroke\n",i+50,i+50);
				fprintf(fpw,"%d 27 moveto %d 283 lineto\n.8 setgray\nstroke\n0 setgray\n",i+50,i+50);
				fprintf(fpw,"%d 15 moveto\n",i+50-17);
				fprintf(fpw,"(%3d) show\n",i);
			}
			if (i < 255)
				fprintf(fpw,"%d %ld moveto %d %ld lineto stroke\n",j,27 + hist[i],j+1,27 + hist[i+1]);
		}

		fputs ("50 27 moveto 50 283 lineto stroke\n",fpw);
		fputs ("50 27 moveto 306 27 lineto stroke\n",fpw);
		fprintf(fpw,"showpage");
		return 0;
	}



    //************* S-FUNCTION ***********//

     int sfunc(int d[])
  
   {
      float u[100],a,b,c,xa,ya,za,bm[100],fuzzy_ent[100],f_ent,s_ent[100],la,lb;
      int i,j=0,xy,nofe;
      float fuzzy_entropy_threshold; 
       float fe_max,th;
       float sum_s_ent;
      b=(float)lmin+(w/2);
         
   while(b<=lmax)
  {     
        
      a=b-(w/2);
      c=b+(w/2);
      ya=(c-a)*(c-a);
      za=(c-a)*(c-a);
 //     printf("\n%f\n%f\n%f\n%d\n%d\n",a,b,c,lmin,lmax);
   
        for(i=lmin;i<=lmax;i++)
	{
//           printf("d[%d]=%d",i,d[i]);
         if(i<a)
          u[i]=0;   
         else if(i>=a && i<=b)
          { 
             xa=2*((float)i-a)*((float)i-a);
             u[i]=xa/ya;
	  }          
  	else if(i>b && i<=c)        
          {
               xa=2*((float)i-c)*((float)i-c);
               u[i]=1-(xa/za);
       	  }
          else
           u[i]=1;

        }
   for(i=lmin;i<=lmax;i++)
//   printf("u[%d]=%f\n",i,u[i]);

     //******* FUZZY ENTROPY  *********//
 
// float f_ent,s_ent[100],la,lb;
  
  for(i=lmin;i<=lmax;i++)
{ 
     if(u[i]==0 || u[i]==1)
     {
      s_ent[i]=0;
      }
   else{  
        la=log(u[i]);
//printf("\n%f",la); 
        lb=log(1-u[i]);
//printf("\n%f",lb);
        s_ent[i]=-(u[i]*la)-((1-u[i])*lb);  
  //    printf("\nShan_Ent[%d]=%f\n",i,s_ent[i]);
       }
 }
 
  for(i=lmin;i<=lmax;i++)
{
//    printf("\nShan_Ent[%d]=%f\n",i,s_ent[i]);
//  if(s_ent[i]==NaN)
  //   s_ent[i]=0;
}
 for(i=lmin;i<=lmax;i++)
//   printf("\ns_ent[%d]=%f",i,s_ent[i]);
  

//int xy;

xy=x*y;
 
   for(i=lmin;i<=lmax;i++)
//     printf("%d\n",d[i]); 
  
//printf("xy=%d",xy);
 
//float sum_s_ent=0.00;
     sum_s_ent=0.00;

   for(i=lmin;i<=lmax;i++)
  {
    sum_s_ent=(sum_s_ent+s_ent[i]*d[i]);

  }
  

  f_ent=sum_s_ent;

// printf("\nFuzzy Entropy for b=%f is %f\n",b,f_ent);
        
bm[j]=b;
fuzzy_ent[j]=f_ent;

j++;
b++;

nofe=j;


 }//End of While


  for(i=0;i<nofe;i++)
// printf("\nFuzzy Entropy for b=%f is %f\n",bm[i],fuzzy_ent[i]);

 
// printf("\nThreshold is selected by the calculation of local minima of the Fuzzy Entropys \n");
   
   fuzzy_entropy_threshold=fuzzy_entropy_localminima(fuzzy_ent,nofe,bm);

//printf("\nThreshold value for Image Segmentation as determined from Fuzzy Entropy is =%f\n",fuzzy_entropy_threshold);



  

  

    //******** FUZZY CORRELATION ***********//



  
 
  float x2,x1,sum_x1x2,u_ideal[100],f_corr,fuzzy_corr,fuzzy_correlation[100],nofc,bcorr[100],fuzzy_correlation_threshold;

  int l=0;

   b=(float)lmin+w/2;
//   b=35;
    while(b<=lmax)
  {
   x2=0.00;
   for(i=lmin;i<=lmax;i++)  
     x2=x2+(((2*u[i]*d[i])-1)*((2*u[i]*d[i])-1));

//     printf("\nX2=%f\n",x2);


    for(i=lmin;i<=lmax;i++)
    {
        if(i<b)
        u_ideal[i]=0;
        else
         u_ideal[i]=1;
     }


    f_corr=0.00;
    x1=0.00;
    for(i=lmin;i<=lmax;i++)
   {
     
     x1=x1+(((2*u_ideal[i]*d[i])-1)*((2*u_ideal[i]*d[i])-1));  
     }
  //    printf("\nX1=%f\n",x1);
     
     sum_x1x2=x1+x2;

       if(sum_x1x2==0)
         fuzzy_corr=1;
       else
     {
       for(i=lmin;i<=lmax;i++)
        f_corr=f_corr+((u_ideal[i]-u[i])*(u_ideal[i]-u[i])*d[i]*d[i]);
       

       //   for(i=lmin;i<=lmax;i++)   
      //    printf("\nf_corr=%f\n",f_corr);
        
       fuzzy_corr=1-4*(f_corr/sum_x1x2);
     
 // printf("\nFuzzy Correlation=%f",fuzzy_corr); 
     }
         

         fuzzy_correlation[l]=fuzzy_corr;
          bcorr[l]=b;
   b++;
   l++;
   nofc=l;
  }//End of 2nd While
  
for(i=0;i<nofc;i++)
printf("Fuzzy Correlation for b=%f is %f\n",bcorr[i],fuzzy_correlation[i]);


fuzzy_correlation_threshold=fuzzy_correlation_localmaxima(fuzzy_correlation,nofc,bcorr);

printf("\nThreshold value for Image Segmentation as determined from Fuzzy Correlation is =%f\n",fuzzy_correlation_threshold);




   return 0;
  }




          //********** MAIN *********//

int main()
{
	FILE *f1;
	int i=0,j=0,loc,count[FREQ],lmi,lma,c;
	unsigned char s,n1[MAX];
	unsigned char im[SIZ][SIZ],copy[SIZ][SIZ];
	printf("\nEnter input file name: ");
	scanf("%s",n1);
	printf("\nEnter image size: ");
	scanf("%d%d",&x,&y);
	f1=fopen(n1,"r");
	if(f1==NULL)
	{
	printf("FILE CAN NOT BE OPENED!....\n\n");
	exit(0);
	}	 
	for(i=0;i<x;i++)
	for(j=0;j<y;j++)
	{
		s=fgetc(f1);
		im[i][j]=s;
		copy[i][j]=s;
	}
	fclose(f1);
//        printf("_____________FOR ORIGINAL DATA_____________\n");
	histo(im,count);
//	printf("Histogram has been succesfully created....\n");
//	creat_image(im);
        sfunc(count);
 
//	loc=loc_min(count,lmin,lmax);
      //  loc=72;
//	printf("\nloc is %d\n",loc);
	lmi=lmin;
	lma=lmax;
//	printf("\nDo you want to do any modifications....\n1:Yes\n2:No\nyour choice :: ");
//	scanf("%d",&i);
	if(i==1)
	{
//	modify(im);
//        printf("------------------FOR MODIFIED DATA------------\n");
//	histo(im,count);
//	printf("Histogram has been created....\n");
//	creat_image(im);
        
	}
        for(i=lmin;i<=lmax;i++)
//        printf("c[%d]=%d",i,count[i]);  
//	threshold(copy,loc);
 //       printf("\n----------------AFTER THRESHOLDING----------------------\n");
//	creat_image(copy);
//	printf("\nALL THE FILES HAVE BEEN SAVED SUCCESSFULLY IN YOUR CURRENT DIRECTORY......\n\n");	
	

  return 0;

 }

