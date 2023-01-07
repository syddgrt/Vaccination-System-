#include<iostream>
#include<string>
#include<iomanip>
#include<cctype>

using namespace std;

class personalInfo {
protected:
	string name, passportNo; //create/personal information objects of class personal Info under protected (so that derived class can access)
	char gender;
	int age;

public:
	void readInfo(); //method to read personal informations from user input
	string getPassportNo() { //getters for passportNo
		return passportNo;
	}
	int getAge() {//getters for age
		return age;
	}
	char getGender() {//getters for gender
		return gender;
	}

};
void personalInfo::readInfo() {

	cin.ignore();
	getline(cin, name); //get line (if name contains spaces (etc;syed haikal))
	do { //loop if input is M,m or F,f
		cout << "Enter gender(M/F): ";
		cin >> gender;
	} while (gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f');

	cout << "\nMalaysia passport must be 9 characters long (X00000000)" << endl;

	cout << "Enter passport number: ";
	cin >> passportNo;

	if (passportNo.size() != 9)
	{
		do //make sure passport is 9 characters long(loop if not)
		{
			cout << "Invalid Passport Number" << endl;
			cout << "Please re-enter(Passport must be 9 characters long (X00000000))" << endl;
			cin >> passportNo;
		} while (passportNo.size() != 9);

	}

	cout << "Enter age: ";
	do 
	{
		cin >> age; // enter age
		if(age<=11)
		{
			cout<<"\nInvalid age(must be 12 and above)\n";
		}

	} while (age <=11);
}
	

class vaccinationStatus :virtual public personalInfo {
protected:
	string Status; //create object Status and StatusNum of type  string and int respectively under class vaccinationStatus
	int StatusNum;
public:
	void readStatus(); //method to read vaccination statuses from user input
	int getStatusNum() { //getter for StatusNum
		return StatusNum; 
	}
};
void vaccinationStatus::readStatus() {


	if (StatusNum == 2) //if StatusNum is 2 (which is PARTIALLY VACCINATED) 
	{
		cout << "\nChoices are: 1 for fully vaccinated\n\t    " << endl; //Display the only choice the user has which is to be FULLY VACCINATED
	}
	else if (StatusNum == 3) //if StatusNum is 2 (which is NOT YET VACCINATED) 
	{
		cout << "\nChoices are: 1 for fully vaccinated\n\t     2 for partially vaccinated\n\t    " << endl; //Display the only choice user has which is to be PARTIALLY or FULLY VACCINATED
	}
	else
		cout << "\nChoices are: 1 for fully vaccinated\n\t     2 for partially vaccinated\n\t     3 for not yet taken." << endl; //ELSE DISPLAY ALL CHOICES IF NO STATUSNUM INPUT BEFORE
	do
	{
		cout << "Enter your vaccination status: "; // ENTER STATUS
		cin >> StatusNum;
		if (StatusNum == 1)
		{
			Status = "Fully Vaccinated";
		}
		else if (StatusNum == 2)
		{
			Status = "Partially Vaccinated";
		}
		else if (StatusNum == 3)
		{
			Status = "Not yet taken";
		}
		else
		{
			cout << "Invalid Input";
		}
	} while (StatusNum != 1 && StatusNum != 2 && StatusNum != 3); // LOOP IF INVALID USER INPUT

}

class vaccinationInfo :virtual public personalInfo {
private:
	string Type, Date1, Date2; //create object Type,Date1,Date2 which are data type string and 							  
	int TypeNum;			   //TypeNum of data type int i under class vaccinationInfo
public:
	void readVac(); //method to read vvaccination informations from user input
	string getType(){	//getter for Type
		return Type;
	}
	string getDate1(){	//getter for Date1
		return Date1;
	}
	string getDate2(){	//getter for Date2
		return Date2;
	}
	int getTypeNum() { //getter for TypeNum
		return TypeNum;
	}

};
void vaccinationInfo::readVac() {
	cout << "Choices are: 1 Pfizer\n\t     2 Astra-Zeneca\n\t     3 Sinovac\n\t     " << endl;
	do
	{
		cout << "Enter the type of vaccine you took: "; //prompt user to input the type of vaccine they took
		cin >> TypeNum;
		if (TypeNum == 1)
		{
			Type = "Pfizer"; 
		}
		else if (TypeNum == 2)
		{
			Type = "Astra-Zeneca";;
		}
		else if (TypeNum == 3)
		{
			Type = "Sinovac";
		}
		else
			cout << "\nInvalid Input!\n";
	} while (TypeNum != 1 && TypeNum != 2 && TypeNum != 3);

	cout << "Enter your vaccine appointment dates(XX/XX/XXXX)" << endl; //prompt user to enter the date they got their vaccines
	cout << "Date 1 :";
	cin >> Date1;

	cout << "Date 2 :";
	cin >> Date2;
	cout << "\n";
}

class allInfoCombined :public vaccinationStatus{
protected:
	int counter; //int counter for statistics purposes
	vaccinationInfo obj; //COMPOSITION (Gives access to all objects in class vaccinationInfo to class allInfoCombined (without using inheritance)
public:
	void readAll(); //method to read ALL 3 information bundle from prior read methods.
	void printAll(); // method to print ALL 3 informations after reading all of them
	friend void interface(); //FRIEND function to gain access to all class data for main
};
void allInfoCombined::readAll() {

	personalInfo::readInfo(); //Method to get user personal informations
	vaccinationStatus::readStatus(); //Method to get user statuses
	//Based on user input status from readStatus(), the program will determine wether the user need to input vaccination type and dates or not.
	if (StatusNum == 1) {
		cout << "\nYou are already fully vaccinated!\n" << endl;
		obj.readVac(); //User has to input vaccine type and both vaccination appointment dates
	}
	else if (StatusNum == 2) {
		cout << "\nYou are not fully vaccinated yet\n" << endl;
		obj.readVac(); //User has to input vaccine type and both vaccination appointment dates
	}

	else if (StatusNum == 3) {
		cout << "\nYou have not been vaccinated yet." << endl;
		cout << "Please wait for your vaccine appointments\n" << endl;
		//User dont have to input vaccine type and both vaccination appointment dates
	}
}
void allInfoCombined::printAll() {
	cout << setw(20) << left << name << setw(20) << left << gender << setw(20) << left << passportNo << setw(20) << left << age << setw(20) << left << Status << "\t" << setw(20) << left << obj.getType() << setw(20) << left << obj.getDate1() << setw(20) << left << obj.getDate2() << endl;
	//Just a program to display all informations stored in a tablature.
}
void interface() {

	//FRIEND FUNCTION

	int size = 0; //declare size (for array)
	int mainChoice; //mainChoice for menu

	allInfoCombined allInfo[100]; //create object array allInfo of type class allInfoCombined


	cout << " \t\t\t\t*****************************************" << endl;
	cout << " \t\t\t\t*                                       *" << endl;
	cout << " \t\t\t\t*    VACCINATION INFORMATION SYSTEM     *" << endl;
	cout << " \t\t\t\t*                                       *" << endl;
	cout << " \t\t\t\t*****************************************" << endl;
	do
	{
		cout << "\nMain Menu" << endl;								//Main menu choices
		cout << "1. Enter Personal Information." << endl;
		cout << "2. Update Vaccination Information" << endl;
		cout << "3. Statistics" << endl;
		cout << "4. EXIT" << endl;
		cout << "Choice is : ";
		cin >> mainChoice;

		if (mainChoice == 1) // Input informations(personal info, vaccination status and vaccination info)
		{
			cout << "How many personal informations: ";
			cin >> size;
			cout << "\n";
			for (int i = 0; i < size; i++) //loop to read all personal informations based on sample size
			{
				cout << "Enter name[" << i + 1 << "]: ";
				allInfo[i].readAll(); // informations from readAll will be inserted into the array allInfo[i]
			}
			cout << "ALL INFORMATIONS" << endl;
			cout << setw(20) << left << "NAME" << setw(20) << left << "GENDER" << setw(20) << left << "PASSPORT-NO" << setw(20) << left << "AGE" << setw(20) << left << "STATUS" << "\t" << setw(20) << left << "TYPE" << setw(20) << left << "1ST APPOINTMENT" << setw(20) << left << "2ND APPOINTMENT" << endl;
			for (int i = 0; i < size; i++) //loop to display all personal informations based on sample size
			{
				allInfo[i].printAll(); // print every information that have been stored from prior allInfo[i].readAll() statement
			}

		}
		else if (mainChoice == 2) // Update vaccination information that is already in the system
		{
			if (size == 0) // If there is no prior user input from mainChoice==1 . mainChoice==2 cannot be used properly.
			{
				cout << "There are no informations available..." << endl; 
			}
			else
			{
				string passportNoUpdate; //declare new variable passportNoUpdate (user input for update)
				cout << "\nALL INFORMATIONS" << endl;
				cout << setw(20) << left << "NAME" << setw(20) << left << "GENDER" << setw(20) << left << "PASSPORT-NO" << setw(20) << left << "AGE" << setw(20) << left << "STATUS" << "\t" << setw(20) << left << "TYPE" << setw(20) << left << "1ST APPOINTMENT" << setw(20) << left << "2ND APPOINTMENT" << endl;
				for (int i = 0; i < size; i++)
				{
					allInfo[i].printAll(); // print every information that have been stored from prior allInfo[i].readAll() statement
				} 
				cout << "\nWhich personal information do you wish to update?" << endl;
				cout << "Enter passport: ";
				cin >> passportNoUpdate; //user input passport number which they want to update the vaccination information

				for (int i = 0; i < size; i++)
				{
					if (allInfo[i].getPassportNo() == passportNoUpdate) //Comparing input passport number with the ones already in the system (array)
					{												//Search for the similar passport number to update	
						cout << "\nInformation Found!" << endl; // If the passportNoUpdate matches with the one in the system
						cout << "Enter new vaccination status" << endl; 


						if (allInfo[i].getStatusNum() == 2) //If PARTIALLY VACCINATED. DONT NEED TO READ VACCINATION INFO AS THEY HAVE ALREADY BEEN INPUTTED BEFORE
						{
							allInfo[i].readStatus();
							cout << "\nInformationUpdated!" << endl;
						}
						else if (allInfo[i].getStatusNum() == 3) //If NOT YET VACCINATED.NEED TO READ VACCINATION INFO AS THEY HAVE ALREADY BEEN INPUTTED BEFORE
						{
							allInfo[i].readStatus();
							allInfo[i].obj.readVac(); 
							cout << "\nInformation Updated!" << endl;
						}
						cout << setw(20) << left << "NAME" << setw(20) << left << "GENDER" << setw(20) << left << "PASSPORT-NO" << setw(20) << left << "AGE" << setw(20) << left << "STATUS" << "\t" << setw(20) << left << "TYPE" << setw(20) << left << "1ST APPOINTMENT" << setw(20) << left << "2ND APPOINTMENT" << endl;
						for (int i = 0; i < size; i++)
						{
							allInfo[i].printAll();  // print every information that have been stored from prior allInfo[i].readAll() statement after updates
						}
					}
				}
			}


		}
		else if (mainChoice == 3) //Statistics from all informations
		{
			int statsChoice = 0;
			if (size == 0) // If there is no prior user input from mainChoice==1 . mainChoice==3 cannot be used properly.
			{
				cout << "There are no informations available..." << endl;
			}
			else
			{
				do
				{
					int statsChoice = 0;
					cout << "\n\t1.Vaccination Status Statistics" << endl;
					cout << "\t2.Vaccine Type Statistics" << endl;
					cout << "\t3.Vaccination Information (AGE)" << endl;
					cout << "\t4.Vaccination Information (Gender)" << endl;
					cout << "\t5.Return to main menu\n" << endl;
					cout << "Enter your choice : ";
					cin >> statsChoice;
					if (statsChoice == 1) //Vaccination Status stastistics
					{
						int counter1 = 0;
						int counter2 = 0;
						int counter3 = 0;
						for (int i = 0; i < size; i++)
						{
							//add 1 to counter depend on the vaccination status choices that has been input by the user
							if (allInfo[i].getStatusNum() == 1)
							{
								counter1 = counter1 + 1;
							}
							else if (allInfo[i].getStatusNum() == 2)
							{
								counter2 = counter2 + 1;
							}
							else if (allInfo[i].getStatusNum() == 3)
							{
								counter3 = counter3 + 1;
							}
						}
						cout << "\n\tFULLY VACCINATED : " << counter1 << endl;
						cout << "\tPARTIALLY VACCINATED : " << counter2 << endl;
						cout << "\tNOT YET VACCINATED : " << counter3 << endl;
						//print total counter value based on vaccination statuses


					}
					if (statsChoice == 2)//Vaccine type statistics
					{
						int counter1 = 0;
						int counter2 = 0;
						int counter3 = 0;
						for (int i = 0; i < size; i++)
						{
							//add 1 to counter depend on the vaccine type choices that has been input by the user
							if (allInfo[i].obj.getTypeNum() == 1)
							{
								counter1 = counter1 + 1;
							}
							else if (allInfo[i].obj.getTypeNum() == 2)
							{
								counter2 = counter2 + 1;
							}
							else if (allInfo[i].obj.getTypeNum() == 3)
							{
								counter3 = counter3 + 1;
							}
						}
						cout << "\n\tPFIZER : " << counter1 << endl;
						cout << "\tASTRA-ZENECA : " << counter2 << endl;
						cout << "\tSINOVAC : " << counter3 << endl;
						//print total counter value based on vaccine type

					}
					if (statsChoice == 3) //Age range statistics
					{
						int counter1 = 0;
						int counter2 = 0;
						int counter3 = 0;
						for (int i = 0; i < size; i++)
						{

							//add 1 to counter depend on the age range that has been input by the user
							if (allInfo[i].getAge() >= 12 && allInfo[i].getAge() <= 18)
							{
								counter1 = counter1 + 1;
							}
							if (allInfo[i].getAge() >= 19 && allInfo[i].getAge() <= 39)
							{
								counter2 = counter2 + 1;
							}
							else if (40 <= allInfo[i].getAge())
							{
								counter3 = counter3 + 1;
							}
						}
						cout << "\n\tAge(12 - 18) : " << counter1 << endl;
						cout << "\tAge(19 - 39) : " << counter2 << endl;
						cout << "\tAge(40 and above) : " << counter3 << endl;
						//print total counter value based on age ranges
					}
					if (statsChoice == 4)//gender statistics
					{
						int counter1 = 0;
						int counter2 = 0;
						for (int i = 0; i < size; i++)
						{
							//add 1 to counter depend on the gender that has been input by the user
							if (allInfo[i].getGender() == 'M' || allInfo[i].getGender() == 'm')
							{
								counter1 = counter1 + 1;
							}
							else if (allInfo[i].getGender() == 'F' || allInfo[i].getGender() == 'F')
							{
								counter2 = counter2 + 1;
							}
						}
						cout << "\n\tMALE : " << counter1 << endl;
						cout << "\tFEMALE : " << counter2 << endl;
						//print total counter value based on gender 
					}
				} while (statsChoice != 5);
			}
		}
		else if (mainChoice == 4) //Exit
		{
			cout << "\nPROGRAM EXITED...";
		}
		else 
		{
			cout << "\nPlease re-enter choice!";
		}
		cout << endl;

	} while (mainChoice != 4);
}
int main() {

	interface(); // call friend function interface to display menu and user interface

}
