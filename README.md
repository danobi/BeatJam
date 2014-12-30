BeatJam
=======

A new twist on the classic rhythm game genre

How to do a local build
=======

- First generate the Makefile using cmake
	- Run:
		- python /path/to/oxygine-framework/tools/gen_template.py BeatJam -t cmake -s ~/path/to/BeatJam/src -d ~/path/to/BeatJam/proj.cmake
		- Enter the proj.cmake directory and run "cmake ."
	- Then run "make" in the proj.cmake directory
	- ./BeatJam

Known bugs
=======
- If two beats hit the consume zone too close to each other (~2 subbeats apart), the consume zone border will persist
