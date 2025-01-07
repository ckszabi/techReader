#include "keyValuePairs.h"

// Input from here: 
//.     https://github.com/TomasWallflower/Tech-CS-505/blob/master/CODES.txt
//.     https://dzien.net/tech/index.php?baza=slownik

keyValuePairs<int, String> nameMapping2 {
//    [0000] => None 
//    [0001] => Test 
//    [0002] => Run 
//    [0003] => Break 
//    [0004] => Run support
//    [0005] => Break support 
//    [0006] => Manual run 
//    [0007] => Feeder delay 
//    [0008] => Blower delay 
//    [0009] => Temperature does not increase 
//    [000A] => Central heating sensor damaged 
//    [000B] => Central heating temperature too high 
//    [000C] => Hot water temperature too high 
//    [000D] => Damaged hot water sensor 
//    [000E] => Damaged feeder sensor 
//    [000F] => Too high feeder temperature 
//    [0010] => Grate 
//    [0011] => Failed ignition 
//    [0012] => Damaged exhaust gas outlet sensor 
//    [0013] => Damaged return sensor 
//    [0014] => Engine thermal 
//    [0015] => No communication 
//    [0016] => No fuel 
//    [0017] => Reed switch 
//    [0018] => Thermal protection 
//    [0019] => Transition phase failed 
//    [001A] => Extinguished 
//    [001B] => Floor sensor damaged 
//    [001C] => Fan short circuit 
//    [001D] => Valve sensor damaged 
//    [001E] => Manual operation [ 
//    [001F] => Ignition 
//    [0020] => Charging 
//    [0021] => Disabled 
//    [0022] => Extinguishing 
//    [0023] => Ignition 
//    [0024] => Ignition 
//    [0025] => Cleaning the grate [ 
//    [0026] => Switching off the addition 
//    [0027] => Initial shutdown of the grate 
//    [0028] => Second phase of switching off 
//    [0029] => Waiting to disable refilling 
//    [002A] => Standby 
//    [002B] => Transition phase 
//    [002C] => Transition phase 
//    [002D] => Ignition delay 
//    [002E] => Modulation operation 
//    [002F] => Modulation break 
//    [0030] => Test feeder - waiting 
//    [0031] => Feeder test 
//    [0032] => Blowing test 
//    [0033] => Central heating pump test 
//    [0034] => Hot water pump test 
//    [0035] => Recording test - waiting 
//    [0036] => Test recording 
//    [0037] => Setting the service code 
//    [0038] => Adding - waiting 
//    [0039] => Switching off the addition 
//    [003A] => Extinguishing 
//    [003B] => Exhaust 
//    [003C] => Exhaust 
//    [003D] => Fire test 
//    [003E] => 62 
//    [003F] => Softstart 
//    [0040] => Soft start 
//    [0041] => Work - waiting
//    [0042] => Fan calibration 
//    [0043] => Exhaust gas sensor test 
//    [0044] => 68 
//    [0045] => T2 maintenance interval 
//    [0046] => T2 maintenance operation 
//    [0047] => Feeder delay 
//    [0048] => Delay airflow 
//    [0049] => Operation without PID 
//    [004A] => Maintenance break without PID 
//    [004B] => Maintenance operation without PID 
//    [004C] => Snail pre-alarm 
//    [004D] => Incorrect fan selection 
//    [004E] => Ignition 
//    [004F] => Ignition 
//    [0050] => Maintain 
//    [0051] => Message 
//    [0052] => Supervision 
//    [0053] => Manual Burn 
//    [0054] => Manual Burn 
//    [0055] => Manual Burn 
//    [0056] => Fire Test 
//    [0057] => Fire test 
//    [0058] => Fire test 
//    [0059] => Feeder advance 
//    [005A] => Feeder return 
//    [005B] => Blowing operation in supervision 
//    [005C] => Blowing pause in supervision 
//    [005D] = > Soft start 
//    [005E] => Transition phase 
//    [005F] => Support disabled 
//    [0060] => Pause 
//    [0061] => Fuel consumption measurement 
//    [00C8] => Fan control sensor defective 
//    [00C9] => Hall effect sensor 
//    [00CA] => Additional pump sensor damaged 
//    [00CB] => Fan control temperature too high 
//    [00CC] => 204 
//    [00CD] => No communication with the valve 
//    [00CE] => Weather sensor damaged 
//    [00CF] => Floor temperature too high 
//    [00D0 ] => Second buffer sensor damaged 
//    [00D1] => Maid sensor damaged 
//    [00D2] => Buffer sensor damaged 
//    [00D3] => Feeder hall effect sensor 
//    [00D4] => Solar sensor 1 damaged 
//    [00D5] => Solar sensor 2 damaged 
//    [00D6 ] => Solar sensor 3 damaged 
//    [00D7] => Solar sensor 4 damaged 
{500, "Driver status"},
{501, "Temperature measured CO"},
{502, "Demanded central heating temperature (from the regulator)"},
{503, "503"},
//    [0000] => inactive 
//    [0001] => active 
{505, "Regulator status"},
{509, "Version"},
//    [0000] => no 
//    [0001] => yes 
{510, "hand work"},
//    [0000] => not working 
//    [0001] => working 
{511, "Feeder operation"},
//    [0000] => stop 
//    [0001] => run
{512, "Fan operation"},
//    [0000] => stop 
//    [0001] => run 
{513, "Central heating pump operation"},
//    [0000] => stop 
//    [0001] => run 
{515, "Hot water pump operation"},
//    [0000] => stop 
//    [0001] => run 
{521, "Lighting"},
//    [0000] => stop 
//    [0001] => start 
{522, "Fade out"},
{531, "Fan speed percentage"},
{536, "FRAME: end (checksum)"},	
{543, "Driver type"},
//    [0000] => stop 
//    [0001] => run 
{546, "Circulation pump operation"},
//    [0000] => stop 
//    [0001] => run 
{547, "Floor pump operation"},
{548, "Valve opening percentage"},
{549, "Cancel Alarm"},
//    [0000] => to-> all devices 
//    [FFF4] => to-> ethernet module 
//    [FFFA] => to-> Tech room controller	 
//    [FFF8] => to-> GSM module 
{550, "FRAME: beginning"},
{559, "Temp. exhaust gases measured"},
//    [0000] => house heating 
//    [0001] => boiler priority 
//    [0002] => parallel pumps 
//    [0003] => summer mode 
{581, "Pump mode"},
//    [0000] => Off 
//    [0001] => On 
{648, "Standby"},
{652, "Valve temperature"},
{654, "Set hot water temperature (from the regulator)"},
{664, "Regulator time"},
//    [0000] => Sunday 
//    [0001] => Monday 
//    [0002] => Tuesday 
//    [0003] => Wednesday 
//    [0004] => Thursday
//    [0005] => Friday 
//    [0006] => Saturday 
{665, "Day of the week of the regulator"},
//    [0001] => CO 
//    [0002] => floor 
{668, "Valve type"},
{742, "Temperature measured hot water"},
{759, "Valve setting (from the regulator)"},
//    [0001] => enabled 
//    [0000] => disabled 
{760, "Valve function"},
{761, "Temperture outside"},
{764, "Changing the set central heating temperature"},
{769, "RC"},
{785, "Temp. peaceful measured"},
{786, "Set room temperature"},
//    [5A2D] => 45-90 degrees 
{790, "minMax CO"},
{791, "minMax hot water"},
{802, "There is fuel"},	
{806, "Operation of the additional pump"},
//    [0001] => floor 
//    [0004] => circulating 
{808, "Type of additional pump"},
//    [0001] => on 
//    [0000] => off 
//    [] => firing up 
{817, "Valve pump"},
//    [FFF0] => Built-in valve 2 
//    [FFF1] => Built-in valve 1 
{826, "Valve address"},	
//    [] => 10-55 
{827, "minMax of the valve"},
//    [0000] => with reheating 
{835, "A type of summer mode"},
{867, "867"},
{869, "869"},		
{871, "871"},
{873, "Fuel level"},
{874, "Fuel remaining hours"},
{880, "Temperature feeder measured"},
{887, "887"},	
{898, "Changing the valve setting"},
//    [0000] => connection active 
//    [0001] => internet module is disconnected 
{899, "Status of the web module"},
//    [0000] => connection active 
//    [0001] => main controller is disconnected 
{903, "Main controller status"},
{1028,"Set room temperature min-max"},
{1029,"Users set room temperature"},
{1030,"Set room temperature correction"},

{2440,"2440"},
{2540,"2540"},

//    [0002] => operation 
//    [0082] => supervision 
//    [0009] => alarm: Temperature does not rise 
//    [000E] => alarm: CO sensor damaged 
//    [000A] => alarm: Feeder sensor damaged 
//    [0031] => firing up 
//    [0027] => alarm: Floor sensor damaged 
//    [0029] => alarm: Valve sensor damaged 
//    [0052] => supervision mode 
//    [0050] => support (operation without PID), ST-755 controller with PID Stalmark 
{5500,"Driver status (1)"},
{5501,"Measured central heating temperature"},
{5502,"Set central heating temperature"},
//    [0001] => enabled 
//    [0000] => disabled 
{5503,"TECH room regulator"},
//    [0000] => stop 
//    [0001] => run 
{5511,"Feeder"},
//    [0000] => stop 
//    [0001] => run 
{5512,"Blowing fan"},	
//    [0000] => stop 
//    [0001] => run 
{5513,"Central heating pump"},	
//    [0000] => stop 
//    [0001] => run 
{5515,"Hot water pump"},
{5531,"Blower fan speed"},
//    [0016] => ST-730zPID / ST-755 zPid / ST-450 STALMARK? without PID? / ST-500 
//    [0007] => AG LUX (without PID) / K1PRv4PZ / ST-755 / K1PRv2 
//    [0013] => ST-450zPID 
//    [0015] => ST-480 
//    [0009] => ST-37rs 
//    [0008] => ST-709 
//    [0020] => ST-402 
//    [002C] => ST 
//    [0005] => ST- 48 
//    [0006] => TECH / AG LUX 
//    [000A] => TECH i3 
{5543,"Driver type"},
{5545,"Temp. underfloor heating (from the underfloor sensor)"},
//    [0000] => stop 
//    [0001] => run 
{5546,"Hot water circulation pump"},
//    [0000] => stop 
//    [0001] => run 
{5547,"Floor pump"},
//    [0000] => valve (mixing) 
//    [0001] => central heating valve (mixing) 
//    [0002] => floor valve (mixing) 
{5548,"Percentage opening of the built-in valve"},	
{5559,"Exhaust gas temperature"},
//    [0000] => house heating 
//    [0001] => boiler priority 
//    [0002] => parallel pumps 
//    [0003] => summer mode 
{5581,"Pump operating mode"},
{5623,"Temp. turning on the floor pump"},
{5647,"Temp. max floors"},
{5648,"Standby"},
{5652,"Valve temperature (1)"},
{5654,"Set hot water temperature	"},
{5668,"Valve type"},
//    [0000] => stop 
//    [0001] => run 
{5664,"Controller time set"},
//    [0000] => Sunday 
//    [0001] => Monday 
//    [0002] => Tuesday 
//    [0003] => Wednesday 
//    [0004] => Thursday
//    [0005] => Friday 
//    [0006] => Saturday 
{5665,"The set day of the week for the controller"},
{5668,"5668"},
{5742,"Measured hot water temperature"},
//    [0001] => On 
//    [0000] => Off 
{5759,"Valve setting entered"},
{5760,"Valve condition"},
{5761,"Measured outdoor temperature"},
{5785,"5785"},
{5790,"minMax CO"},
{5791,"minMax hot water"},
//    [0000] => stop 
//    [0001] => run 
{5806,"Additional pump state"},
//    [0005] => disabled 
//    [0003] => enabled 
{5808,"Additional pump operation"},
//    [0000] => stop 
//    [0001] => run 
{5814,"Circulation pump"},
//    [0003] => AG-LUXbezPID 
//    [0005] => ST-730zPID 
//    [0008] => ST-450zPID 
//    [0006] => ST-480
{5817,"5817"},
{5887,"Driver type"},
{5880,"Feeder temperature"},
{5825,"Hot water return temperature"},
{5826,"Valve address"},
{5827,"minMax of the valve"},
{5857,"5857"},
{5868,"5868"},
{5871,"Data set number for the valve (from the controller)"},
{5873,"percentage of fuel in the tank"},
{5874,"approximate fuel supply time in hours (updated every 5 minutes)"},
{5881,"Parameter for the previous value"},
//    [0000] => stop 
//    [0001] => run 
{5898,"5898"},
{6001,"Buffer pump"},
{6024,"6024"},
{6204,"6204"},

{7014,"Setting the maximum collector operating temperature"},
};