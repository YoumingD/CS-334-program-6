Just for reference. Copying or plagiarism is not allowed!
The excutable file is named as program 6.

For using "cut off left", "cut off right", "extent left", "extend right",
first enter a s value in the glui controller by typing a number and hit enter buttom.
Then, click the operation you want to do among "cut off left", "cut off right", "extent left", "extend right".
And please click on the sphere once to make sure the change shows.

Hit "set points", then you can use mouse-left click on the sphere to create points.
Hit "set tangents", then you can use mouse-left to create tangents for points.
(same order as you creating the points)
Hit "draw control", then click on the sphere. The control lines will be connected and shows.
Hit "Move control", then you can move the control point by mouse-left.
Hit "Draw curve", then click on the sphere. The curve will be generated and shows.


The "CLEAR" menu will clear all the points and lines. Reset the status.

The "ADJUST" menu will allow you do some manipulations:
Mouse left + shift: define a new point.
Mouse left + control: drags the point that you click 
Mouse left + control + shift:  deletes the targeted point.
The rotation is not achieved, so just using Mouse left can't rotate the sphere.
Since rotation is not asked for program 5, this should be fine.

The "SHOW POLYGON" menu will connect all points with lines that calculated by SLERP algorithm.
The "Hide POLYGON" menu will hide the lines.

Inside the "DECASTELJAU" menu there are 4 submenus:
1. "Show lines" will show all points in the new sequence and connect them. Lines are green, points are blue.
Click "Show line" again can hide those lines and points.
2. "Show F(t)" will show the last point that calculated by DECASTELJAU algorithm, and it's a red point.
Click "Show F(t)" again can hide F(t) point.
3. "Show curve" will show the curve calculated by DECASTELJAU algorithm, and the curve is blue.
Click "Show curve" again can hide this curve.
4. "Change t" will allow you change the t value by using UP or DOWN key on the keyboard. The default t is 0.5.
Click "Change t" again can stop the change funciton.

If you moving, adding, or deleting any points in ADJUST mode, 
you can see the change of all lines and points calculated by DECASTELJAU algorithm in live time.

The Greenwich meridian is colored as green. The equator is colored as yello.
Other longitude and latitude lines are colored as blue with 30 degrees gap.


All function works fine and exactly as the demo video shows.
