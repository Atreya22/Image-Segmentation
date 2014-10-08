
Image Segmentation using fuzzy measures
========================================

Image segmentation is the process that subdivides an image into its constituent parts of objects. It divides an image into parts that have strong correlations with objects to reflect the actual information collected from the real world.The level to which this subdivision is carried out depends on the problem being solved, i.e., the segmentation should stop when the object of interest in an application have been isolated. E.g., in autonomous air-to-ground target acquisition, suppose our interest lies in identifying vehicle in the road, the first step is to segment the road from the image and then to segment the content of the road down to potential vehicles. Image thresholding techniques are used for image segmentation.  

Histogram-Based Segmentation
========================================

Histogram-based image segmentation is one of the most simple and most often used segmentation techniques. It uses the histogram to select the grey levels for grouping pixel into regions. In a simple image there are two entities: the background and the object. The background is generally one grey level and occupies most of the image. Therefore its grey level is a large peak in the histogram. The object or subject of the image is another grey level, and grey level is another, smaller peak in the histogram. 


Disadvantage of Histogram and Threshold Based Segmentation 
================================================================================

•	One problem with histogram based segmentation is choosing the threshold point. Here the point is middle way between two peaks which is always not correct.
•	In case of multilevel thresholding there can be multiple threshold value. So problem occur incase choosing best solved using region growing methods.
•	To get the optimal threshold value we use probability density function. But it does not give the actual object separating from background.
•	In case of images corrupted by noise leading to a multimodal histogram.In this case the ordinary histogram thresholding  technique performed poorly or even fail.


Membership Function:
========================================
       Most of the geometrical properties such as area, perimeter, length, breadth, etc. Are dependent not only on the shape of the image, but also on the membership values. If the object pixels have higher gray levels we can select the standard S function [18] to extract a bright image plane. The S function is defined as follows:
               µ(x) = S(x; a, b, c)
                       = 0                                         if x ≤ a,
                    = 2[(x-a)/(c-a)]2                              if a ≤ x ≤ b,
                    = 1 – 2[(x-c)/(c-a)]2                    if b ≤ x ≤ c,      
                    = 1                                       if c ≤ x,
    With cross-over point b=1/2(a + c) and the window size w=c - a. Thus for a fixed cross over point (say b=s, where the µ value is 0.5), pixels have gray levels >s will have µ values >0.5 and pixels having gray levels <s will have µ values <0.5.



Fuzzy Correlation:
========================================
        Fuzzy correlation can be expressed as
                          C(µ1,µ2) = 1- 4[ ∑∑{µ1mn - µ2mn}2 ] / (x1+x2)
                                          = 1                         if X1+X2 = 0
       Where     X1= ∑∑{2µ1mn -1}2   
                       X2= ∑∑{2µ2mn -1}2
                                 m=1,2,3, ... , M; N = 1,2,5,...., N.
        Here µ1mn and µ2mn  denote  the degree of processing the properties µ1 and µ2 respectively by the(m,n)th pixel and C(µ1,µ2) denotes the correlation between two such properties µ1 and µ2.


The C file named as image_segmentation.c

