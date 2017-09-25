Purpose of PowerTransition:
=========
	The project demonstrates one method about power transition handling for Intel® Software Guard Extensions projects development.

How to build/execution:
=========
Windows:
	1. Make sure you have the Windows SGX SDK package installed.
	2. Open the Visual Studio solution file "PowerTransition.sln". 
	3. Build and execute it directly.
Linux:
	1. Make sure you have the Linux SGX SDK package installed.
	2. Build the project with the prepared Makefile:
		a. Hardware Mode, Debug build:
		    $ make SGX_MODE=HW SGX_DEBUG=1
		b. Hardware Mode, Pre-release build:
		    $ make SGX_MODE=HW SGX_PRERELEASE=1
		c. Hardware Mode, Release build:
		    $ make SGX_MODE=HW
		d. Simulation Mode, Debug build:
		    $ make SGX_DEBUG=1
		e. Simulation Mode, Pre-release build:
		    $ make SGX_PRERELEASE=1
		f. Simulation Mode, Release build:
		    $ make
	3. Execute the binary directly:
		$ ./app
