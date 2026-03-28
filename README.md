# Fit Adjustable Chain On Spline Curve Node
A modified version of UE's control rig node "Fit Chain To Spline Curve" that continuously updates the length of the bone chain, allowing for proper spline behavior with additive poses/bone transform changes at runtime.

<p align="center">
<img width="706" height="839" alt="Capture" src="https://github.com/user-attachments/assets/1f41daed-7816-4ec0-89c5-24e49d406de8" />
</p>

A minor change was made so that the chain length is calculated continuously, rather than only once when the node is initialized. Very minor performance cost as we are using the pre-existing cached bone results to calculate chain length. 

The "Update Chain Length" parameter can be used to toggle this behavior. 
