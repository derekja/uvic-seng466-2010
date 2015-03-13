LogBook for Derek

Jan 13 notes (moved in from previous page)

--I went through the L298 module hardwired test procedures to understand the wiring. This is with one of the small motors with a fan on it so that I can tell direction.

--I hooked up the air hogs batteries, one to the arduino board and one to the L298 board.

--remember to tie the grounds together!!!

--now working with a small motor, spins forward at high speed for 1 sec, backwards halfspeed for one sec.

-- identified switch 1 outputs on joystick, verified function on multimeter

-- installed subclipse to use our google code SVN for checkin

-- created a test2 project in SVN

> -- version 1 is the version with no joystick input that just does the forward/backward spin

> -- version 2 reads the joystick input (turn right/left only for now.. proof of concept) and then runs the motor forward (right) or backward (left) depending on angle

-- the two magic lines to enable Serial.print in eclipse! right after the includes
"extern "C" void cxa\_pure\_virtual(void);
void cxa\_pure\_virtual(void) {}"

-- note that on the joystick that full left is 1024 and full right is 0, need to /4 to get into the same scale as motor output and 255-x for right hand motion (to put 0 in the center of the scale)

-- to read serial from within eclipse you can install the rxtx library from qbang.org. That was down today, so I've been using the serial monitor in the arduino IDE. You need to close the monitor to load the board.

-- note that the small wires make VERY poor connections. We need to come up with better jumper solutions than in my little test today.

Jan 20

-- created an introduction and test scenario document for project 1

Jan 21

-- worked on syncing up to the SVN for the LED and sonar work that Jackson did


-- worked on trying to diagnose a battery problem. Concluded that the dying battery is actually now dead.

-- need a couple of pieces of hardware: header pins for 2nd arduino board, 2nd breadboard

-- put servo motor onto digital pin 10, datasheet: http://www.hitecrcd.com/servos/show?name=HS-55

-- having problems with the servo sample code. Our servo just spins in circles regardless of the value on the pin!

-- OK, using my test2 playground project I finally have it reacting. This is using the pulse width method, not the servo library. I still have something weird going on in the servo library.

-- pulse width is going to be really hard to control accurately without our RTOS.

Jan 22

-- worked up a TODO list with Riley and Jackson

-- created a Project1Remote project to hold the code for the effector

-- fighting with interrupt code. Think I'm finally understanding. I'm going to abandon the servo library in favour of hand-written interrupt code, at least in part so as to understand it better.

-- using interrupt 4 so as not to conflict with the sonar

-- re-wired the joystick that had been unsoldered (!?!)

Jan 23

-- trading email with Jackson about the problem other groups are having with sonar and motors (arduino libraries use multiple interrupts)

-- weird, I get servo motor jumps on connecting and disconnecting the serial port monitor

-- wow! initializing the serial port re-starts everything! I get serial.print statements out of my initialization routine on connecting the serial port. When I purposely put in a motor jump that gets called when I disconnect also, so I gather that the board is reset whenever the serial connection changes...

-- OK, decided to put the servo on timer5 so that it doesn't kill any of the PWMs that we want to use for the regular motors. I've put it on pin40.

-- noticed, BTW, that the PWM pins I was using for the motor come off of timer3, I think. At least they are pins OC3B and OC3C. I don't know if that conflicts with the timer for sonar, but we'll see.

-- cripes, having interrupt problems. Checking in and going home. It's been a long day here...

Jan 24

-- OK, been hitting the interrupts all afternoon and it's just not working. Here are some of the problems:

> -- I can't seem to get a waveform to output without doing it explicitly in the interrupts

> -- when in the interrupts I can set fast PWM modes with a preset TOP, but I can't get either ICRn or OCRRnA TOP values to be registered

> -- could not get digital pin 40 to behave properly, so I dropped back to timer 4 and PWM 7

> -- confused by the fact that I pinMode to 7, but I DDRH |= _BV(DDH4) which is actually pin 16_

-- got the logic analyzer figured out so that I can at least watch the pin outputs directly now

Jan 25

-- spent forever convinced that I was not able to write 16 bit values to the register.

-- aarg. Making no progress on this. going home.

Jan 26

-- ok, fresh look at the problem and it still appears that I am not getting the high byte written but I have no idea why

-- finally, the light breaks through the clouds!!!

-- the arduino libraries are the culprit here. I can make everything work without them present, but if I even call init() then the OCR4A register is screwed. Even if I call no other arduino library in the entire program. ICR4 is usable, so there might be a workaround, but how frustrating.

from todo list:

Derek - due tues-- move servo into an interrupt (like the sonar is)

due Tues -- integrate servo and motor control into the main project (depends on servo integ)

-- working on radio. Not working on the main remote board, so using the open board to try and make a minimal radio project

-- OK basic radio working! still need to move it into the main project and wire the other board...

-- wired into the remote board now. moved pins 7 and 8 to 42 and 43 from Neil's wiring and put it on IRQ4 (pin 19)

-- the servo was working as well, but now it only works one direction! It smells smoky also. I think there is a hardware problem there. Need to find a new one tomorrow.

-- the radio is broadcasting to the base station that Neil set up and is sending sonar readings!

Jan 27

-- got a new servo and wired it in, this one has end stops, so it's a bit harder to tell what it's doing. The circular wheel on the top doesn't help either.

-- arg! Got a new servo from Mantis, hooked it in, and immediately stripped the gears!

-- found a supplier for new gears and ordered 3 sets

Jan 28

-- got the larger servo working, took screenshots of the servo timing on the logic analyzer

-- had a weird jitter problem in the larger servo. Turns out that it is very sensitive to small variations in the timing at certain boundary points. I was looking on the logic analyzer and found that my timing was varying by a single microsecond with a period of 3-4 cycles. This was apparently enough to cause the resting state of the servo to jitter. When I changed the timing so that it was s few microseconds less the jitter went away, so I must have been sitting right on some critical boundary.

--took apart the old hs55 servos and idedntified gear problems vs electrical

--got radio receive working for the most part

--worked with riley on radio send from the base station

--took apart and reassembled the joystick about 3 times, finally seems to be working OK, although not perfectly

--helped another team with servo code

--having a problem with the base station where it runs fine when built on my machine, but doesn't run from riley's machine

Jan 29

-- OK, tracked the problem with the radio stopping after a short period of time. It wasn't a problem of different build settings like we thought. Riley found a wiring problem on the base station board - CE was poorly wired

-- worked on writeups, took pictures and hooked up the logic analyzer to take timing screenshots

-- checked in initial project 1 report document

Jan 30

-- still working on writeups

Jan 31

-- OK, done with writeups. My sections are the intro and pictures, the motor section, the servo section, and the radio section.

Feb 2

-- last writeup touches

-- advice from Mantis to keep everything in the 3rd person

-- not sure I actually agree with that advice, but we'll stick to Mantis' preferred style in future reports. ref: http://www.protrainco.com/essays/passive.htm#1

Feb 3

-- gave demo of project 1 to Mantis

-- started thinking about project 2 design

Project 2

Feb 5

-- worked on a 2 deck design out of the pink styrofoam

-- used a mylar skirt

Feb 6-11 I was at a conference

Feb 12

-- back to working on hovercraft

-- mylar skirt had been extended to cover the entire bottom except for a center hole

-- too much friction, not enough lift

-- lots and lots of air getting pushed back out the top holes

-- went to a direct connection to the battery. Not enough current through the fuse and
L298

Feb 16

-- after web reading, tried a cafeteria tray design

-- actually better lift than our initial design

-- too small, though, and the tray edges present a non-deformable skirt, so it won't go over anything

-- no movement on carpet

Feb 17

-- working on the large foam prototype again

-- added nylon skirt

-- first attempt was to just tack bottom edges down and depend on air escape to the bottom to provide lift

-- not successful

-- next attempt was to cut a hole in the bottom foam layer

-- This was marginally more successful, but still not much lift. OK on tile, not carpet

-- plugging one of the fan holes (and removing the fan, of course) actually helps lift! Strange. not sure what is going on here.

Feb 19

-- problem seems to be the skirt evenness. Jackson tried an approach to even out the skirt which seems marginally more effective.

-- hard to get the skirt even with corners. Considering a move to a round hovecraft

-- I added a deformable skirt to the cafeteria tray and it helped a fair amount

Feb 23

-- breakthrough! Adding a small side skirt to the hovercraft helps. Jackson had the insight to try a vertical mounting and he and I put it together.

-- down to a single fan design now

-- amazingly, having a bottom hole the size of the fan hole is not sufficient! I guess the air turbulence creates too much back pressure. There is a lot of air coming out of the fan backwards. But opening up the bottom hole to be about twice the size of the fan hole reduces backflow to almost zero and provides a remarkable lift improvement!

-- we're now floating on both carpet and tile!

-- losing more air out of the skirt than we want, though, so added a layer of duct tape to stiffen the skirt. This seems to help. We now float well with both battery and control board mounted.

-- still need to rig a directional fan, the servo to control the fan, and the sonar. Gonna be tight on this project, but I'm happy to see some hovering!

Feb 26

-- lift is fine with no weight on the hovercraft, but when the thrust motors and L298 is put on board the backdraft gets really bad

-- seems to be a result of our fan not containing the air sufficiently

-- tried to take a big CPU fan and connect our motor to it, but couldn't get the connection right

-- Jackson was working on upping the size of our thrust motor since we weren't really moving

-- decided to get an enclosed fan

Feb 27

-- I found a 12V leaf blower

-- the battery that came with it is really too heavy, but it's there if we get more efficient in our design

-- two of our big battery packs together make 15V which is not so far over the 12V rating to risk the motor

-- taking the control board power off the center of our two big batteries in series

-- mounted leaf blower motor and put batteries in the fan compartment to keep the weight as low as possible

-- we get good lift!

-- for some reason, though, our control board spazzes out when the lift fan is blowing. Too much current draw?

-- may have to use a small battery for the board and thrust motor

-- attached current sensor resistor. Right now we are drawing a full 15amps (.075 V **.005 ohms = 15A)**

Feb 28

-- met with Jackson and Riley and did a test run

-- not enough thrust and direction

-- floating well, though

-- after they left I started rigging up a second servo and fan.

-- the arduino board needs to be powered by 7-12V. The 5 volt regulated output from the L298 is just not enough to drive it reliably. I think that's what was going on with the thing spazzing out when the lift motor was running - it was dropping it's supply just enough to go below some threshhold.

-- the servo motor needs to be driven by 5 volts. 7-12 volts is enough to kill it. Erm, yes, I believe that that is what happened. I think I killed another servo. Fuck. I got one of the little ones mounted, but it's not very nicely mounted and we'll want to tweak it tomorrow.

-- the logic analyzer can create a ground loop! I had assumed that it was high enough impedance not to do that, but the board still ran even when I unplugged the negative lead, with ground going through the logic analyzer. Nothing damaged, thankfully.

-- I had tapped the battery on the negative side instead of the positive when we were taking only one battery to drive the arduino. That was also creating a ground problem. Fixed.