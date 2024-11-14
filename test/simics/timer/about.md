# About the Timer Simics Test

This test performs the following operations and checks:
* Initialize timer to 0x1000
* Set mode to not free running
* Start timer
* Verify timer at start is not 0
* Verify timer expires at 0 -- if so pass, else fail