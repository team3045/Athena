#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"

class Robot: public IterativeRobot
{
	NetworkTable *table;
	RobotDrive rdF;
	RobotDrive rdR;
	Joystick jsE;
	Joystick jsL;
	Joystick jsR;
	Victor vctR;
	Victor vctF;
	Victor vctE;
	Compressor cps;
	DoubleSolenoid ds1;
	DoubleSolenoid ds2;
	DigitalInput diMaxSwitch;
	DigitalInput diMinSwitch;

public:
	Robot() :
		rdF(0, 2),
		rdR(1, 3),
		jsE(2),
		jsL(0),
		jsR(1),
		vctR(4),
		vctF(5),
		vctE(7),
		cps(),
		ds1(0, 1),
		ds2(2, 3),
		diMaxSwitch(0),
		diMinSwitch(1)
	{
		table = NetworkTable::GetTable("");
	}

private:
	void RobotInit()
	{

	}

//	int Counter;
//	int stage;
//	int stageTime[2] = {1000, 2000};
//	int MaxStageNumber;
//	void AutonomousInit()
//	{
//		Counter = 1;
//		stage = 0;
//		MaxStageNumber = 2;
//	}
//
//	bool CheckCounter(int Max){if(Counter <= Max){Counter += 50; return true;}else{Counter = 1; return false;}}
//	void AutonomousPeriodic()
//	{
//		if (this->stage < this->MaxStageNumber)
//		{
//			if (this->CheckCounter(stageTime[stage]))
//			{
//				switch (this->stage)
//				{
//				case 0:
//					break;
//				case 0:
//					break;
//				}
//			}
//			else
//			{
//				this->stage++;
//			}
//		}
//	}

	void TeleopInit()
	{
		printf("Hello world! - From TeleopInit() \n");
		this->cps.Start();
	}

	void Drive()
	{
		//Tank Drive
		float leftInput = -1 * this->jsL.GetY();
		float rightInput = -1 * this->jsR.GetY();
		this->rdF.SetLeftRightMotorOutputs(leftInput, rightInput);
		this->rdR.SetLeftRightMotorOutputs(leftInput, rightInput);
	}

	void TeleopPeriodic()
	{
		this->Drive();

		float elevatorInput = this->jsE.GetY();
		if ((elevatorInput < 0) && (!this->diMaxSwitch.Get()))//elevator up
		{ this->vctE.Set(0); }
		else if ((elevatorInput > 0) && (!this->diMinSwitch.Get()))//elevator down
		{ this->vctE.Set(0); }
		else
		{ this->vctE.Set(elevatorInput); }

		if (this->jsR.GetRawButton(2))//In
		{ this->vctR.Set(-1); this->vctF.Set(1); }
		else if (this->jsR.GetRawButton(3))//Out
		{ this->vctR.Set(1); this->vctF.Set(-1); }
		else
		{ this->vctR.Set(0); this->vctF.Set(0); }

		if (this->jsR.GetRawButton(4))//Close
		{ this->ds1.Set(DoubleSolenoid::kForward); }
		else if (this->jsR.GetRawButton(5))//Open
		{ this->ds1.Set(DoubleSolenoid::kReverse); }
		else
		{ this->ds1.Set(DoubleSolenoid::kOff); }

		if (this->jsE.GetRawButton(4))
		{ this->ds2.Set(DoubleSolenoid::kForward); }
		else if (this->jsE.GetRawButton(5))
		{ this->ds2.Set(DoubleSolenoid::kReverse); }
		else
		{ this->ds2.Set(DoubleSolenoid::kOff); }

		printf("Hello world! - From TeleopPeriodic() \n");
	}

	void TestPeriodic()
	{
//		float speedCoefficient;
//		if (this->jsE.GetRawButton(5))
//		{ speedCoefficient = 0.7; }
//		else if (this->jsE.GetRawButton(7))
//		{ speedCoefficient = 0.3; }
//		else
//		{ speedCoefficient = 1; }
//		if (!this->jsE.GetRawButton(8))
//		{
//			//Tank Drive
//			float leftInput = -1 * this->jsE.GetY();
//			float rightInput = -1 * this->jsE.GetThrottle();
//			this->rdF.SetLeftRightMotorOutputs(leftInput * speedCoefficient, rightInput * speedCoefficient);
//			this->rdR.SetLeftRightMotorOutputs(leftInput * speedCoefficient, rightInput * speedCoefficient);
//			printf("Hello world! - From TestPeriodic() Tank Drive, MotorOutput: %f; %f\n", leftInput * speedCoefficient, rightInput * speedCoefficient);
//		}
//		else
//		{
//			//Arcade Drive
//			float leftInput = -1 * this->jsE.GetY();
//			float rightInput = leftInput;
//			float rotate = this->jsE.GetX();
//			leftInput += rotate;
//			rightInput -= rotate;
//			this->rdF.SetLeftRightMotorOutputs(leftInput * speedCoefficient, rightInput * speedCoefficient);
//			this->rdR.SetLeftRightMotorOutputs(leftInput * speedCoefficient, rightInput * speedCoefficient);
//			printf("Hello world! - From TestPeriodic() Arcade Drive, MotorOutput: %f; %f\n", leftInput * speedCoefficient, rightInput * speedCoefficient);
//		}
//
//		float speedInput = (-1 * this->jsR.GetZ() + 1) / 2;
//		if (this->jsR.GetRawButton(5))
//		{
//			if (!this->diMinSwitch.Get())
//			{
//				this->vctE.Set(-1 * speedInput);
//				printf("Hello world! - From TestPeriodic() ElevatorDown, Speed: %f\n", speedInput);
//			}
//			else
//			{
//				printf("Hello world! - From TestPeriodic() MinSwitchOn");
//				this->vctE.Set(0);
//			}
//		}
//		else if (this->jsR.GetRawButton(4))
//		{
//			if (!this->diMaxSwitch.Get())
//			{
//				this->vctE.Set(1 * speedInput);
//				printf("Hello world! - From TestPeriodic() ElevatorUp, Speed: %f\n", speedInput);
//			}
//			else
//			{
//				printf("Hello world! - From TestPeriodic() MaxSwitchOn");
//				this->vctE.Set(0);
//			}
//		}
//		else
//		{ this->vctE.Set(0); }
//
//		if (this->jsE.GetRawButton(2))
//		{
//			this->vctR.Set(-1);
//			this->vctF.Set(1);
//			printf("Hello world! - From TestPeriodic() WheelIn\n");
//		}
//		else if (this->jsE.GetRawButton(4))
//		{
//			this->vctR.Set(1);
//			this->vctF.Set(-1);
//			printf("Hello world! - From TestPeriodic() WheelOut\n");
//		}
//		else
//		{
//			this->vctR.Set(0);
//			this->vctF.Set(0);
//		}
//
//		if (this->jsE.GetRawButton(1))
//		{
//			this->ds1.Set(DoubleSolenoid::kForward);
//			printf("Hello world! - From TestPeriodic() ClawClosed\n");
//		}
//		else if (this->jsE.GetRawButton(3))
//		{
//			this->ds1.Set(DoubleSolenoid::kReverse);
//			printf("Hello world! - From TestPeriodic() ClawOpened\n");
//		}
//		else
//		{ this->ds1.Set(DoubleSolenoid::kOff); }
		this->Drive();

//		double NTe = this->table->GetNumber("E", 0.0);
//		float elevatorInput = this->jsE.GetY();
//		if ((NTe < 0) && (!this->diMaxSwitch.Get()))//elevator up
//		{ this->vctE.Set(0); }
//		else if ((NTe > 0) && (!this->diMinSwitch.Get()))//elevator down
//		{ this->vctE.Set(0); }
//		else
//		{ this->vctE.Set(elevatorInput); }

		this->table->PutNumber("E", 1.0);
		printf("PutNumber\n");

		if (this->jsR.GetRawButton(2))//In
		{ this->vctR.Set(-1); this->vctF.Set(1); }
		else if (this->jsR.GetRawButton(3))//Out
		{ this->vctR.Set(1); this->vctF.Set(-1); }
		else
		{ this->vctR.Set(0); this->vctF.Set(0); }

		if (this->jsR.GetRawButton(4))//Close
		{ this->ds1.Set(DoubleSolenoid::kForward); }
		else if (this->jsR.GetRawButton(5))//Open
		{ this->ds1.Set(DoubleSolenoid::kReverse); }
		else
		{ this->ds1.Set(DoubleSolenoid::kOff); }

		if (this->jsE.GetRawButton(4))
		{ this->ds2.Set(DoubleSolenoid::kForward); }
		else if (this->jsE.GetRawButton(5))
		{ this->ds2.Set(DoubleSolenoid::kReverse); }
		else
		{ this->ds2.Set(DoubleSolenoid::kOff); }
	}
};

START_ROBOT_CLASS(Robot);
