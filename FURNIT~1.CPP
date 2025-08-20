#include<iostream.h>
#include<conio.h>
#include<process.h>
#include<string.h>
#include<dos.h>
#include<fstream.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<iomanip.h>

class stock
{

    char sto_name[20];
    int sto_quant, sto_id;
    float sto_cost;

public:
void addstock()
    {
    char more='y';

    while(more=='y'||more=='y')
    {
	input();

	ifstream check("stock.txt", ios::binary);
	stock tempu;
	int exist=0;

	while(check.read((char*)&tempu, sizeof(tempu)))
	{
	if(tempu.sto_id==sto_id)
	{
	    exist=1;
	    break;
	}
	}
	check.close();

	if(exist)
	{
	cout<<"\nStock id already exists! Skipping this entry.\n";
	} else
	{
	ofstream out("stock.txt", ios::app|ios::binary);
	out.write((char*)this, sizeof(*this));
	out.close();
	cout<<"\nStock added successfully!";
	}

	cout<<"\n\nDo you want to add another stock? (y/n)->";
	more=getche();
	more=tolower(more);
	while(more!='y'&&more!='n')
	{
	cout<<"\nInvalid input Please Enter 'y' or 'n'->";
	more=getche();
	more=tolower(more);
	}
    }
    }

void input()
    {
    ifstream idin("last_stock_id.txt");
    if(!idin)
	sto_id=2000;
    else
	idin>>sto_id;
    idin.close();

    sto_id++;

    ofstream idout("last_stock_id.txt");
    idout<<sto_id;
    idout.close();

    // validate stock name (only alphabets)
    int validname;
    do
    {
	validname=1;
	cout<<"\nEnter Stock Name->";
	cin>>sto_name;

	for(int i=0; sto_name[i]!='\0'; i++)
	{
	if(!isalpha(sto_name[i]))
	{
	    validname=0;
	    cout<<"Invalid Input(Only Alphabets Allowed)\n";
	    break;
	}
	}
    } while(!validname);

    // validate quantity (only positive numbers)
    char qtyinput[10];
    int validqty;
    do
    {
	validqty=1;
	cout<<"Enter quantity->";
	cin>>qtyinput;

	for(int i=0; qtyinput[i]!='\0'; i++)
	{
	if(!isdigit(qtyinput[i]))
	{
	    validqty=0;
	    cout<<"Invalid input only numbers are allowed\n";
	    break;
	}
	}

	if(validqty)
	{
	sto_quant=atoi(qtyinput);
	if(sto_quant<=0)
	{
	    validqty=0;
	    cout<<"Quantity must be greater than zero.\n";
	}
	}
    } while(!validqty);

    char priceinput[20];
    int validprice;
    do {
	validprice=1;
	int dotcount=0;
	cout<<"Enter price->";
	cin>>priceinput;

	for(int i=0; priceinput[i]!='\0'; i++) {
	if(!isdigit(priceinput[i])&&priceinput[i]!='.')
	{
	    validprice=0;
	    break;
	}
	if(priceinput[i]=='.')
	    dotcount++;
	}

	if(dotcount>1||!validprice)
	{
	validprice=0;
	cout<<"Invalid price. Enter a valid numeric value.\n";
	} else
	{
	sto_cost=atof(priceinput);
	if(sto_cost<=0) {
	    validprice=0;
	    cout<<"Price must be greater than zero.\n";
	}
	}
    } while(!validprice);
    }

void display()
{
    cout.setf(ios::left);
    cout << setw(15) << sto_name;

    cout.setf(ios::right);
    cout << setw(10) << sto_id
     << setw(10) << sto_quant;

    cout.setf(ios::fixed);         // ensure fixed-point
    cout.precision(2);             // two decimal places
    cout << setw(15) << sto_cost;
}

void menu()
    {
    int sto_choice;
    char choiceinput[10];
    getch();
    do
    {
	clrscr();
	cout<<"\n\t                           Main Menu";
	cout<<"                  \n\n\t\t\t1.Press 1 to Enter Stock\n";
	cout<<"                        2.Press 2 to Display All Stock\n";
	cout<<"                        3.Press 3 to Update/Modify Stock\n";
	cout<<"                        4.Press 4 to Delete Stock\n";
	cout<<"                        5.Press 5 to Search Stock\n";
	cout<<"                        6.Press 6 to Display All Buyer\n";
	cout<<"                        7.Press 7 to Delete Buyer\n";
	cout<<"                        8.Press 8 to Update Order Status\n";
	cout<<"                        9.Press 9 to See Delivered or Pending Order\n";
	cout<<"                        10.Press 10 to Check Order Status\n";
	cout<<"                        11.Press 11 to Display All Orders\n";
	cout<<"                        12.Press 12 to Generate A Report\n";
	cout<<"                        13.Press 0 Exit\n";

	cout<<"                    \n\n\t\t\tEnter Your Choice->";
	cin>>choiceinput;

	// validate menu choice
	int validchoice=1;
	for(int i=0; choiceinput[i]!='\0'; i++)
	{
	if(!isdigit(choiceinput[i]))
	{
	    validchoice=0;
	    break;
	}
	}

	if(validchoice)
	{
	sto_choice=atoi(choiceinput);
	} else
	{
	sto_choice=-1; // force default case
	}

	switch(sto_choice)
	{
	case 1:
	    {
	    addstock();
	    break;
	    }
	case 2:
	    {
	    displayallstocks();
	    break;
	    }
	case 3:
	    {
	    updatestock();
	    break;
	    }
	case 4:
	    {
	    deletestock();
	    break;
	    }
	case 5:
	    {
	    searchstock();
	    break;
	    }
	case 6:
	    {
	    displayallbuyer();
	    break;
	    }
	case 7:
	    {
	    deletebuyer();
	    break;
	    }
	case 8:
	    {
	    updateorderstatus();
	    break;
	    }
	case 9:
	    {
	    searchorderstatus();
	    break;
	    }
	case 10:
	    {
	    checkorderstatus();
	    break;
	    }
	case 11:
	    {
	    viewallorders_b();
	    break;
	    }
	case 12:
	    {
	    generatereport();
	    }
	case 0:
	    {
	    return;
	    }
	default:
	    {
	    cout<<"\nInvalid Choice";
	    getch();
	    }
	}
    } while(sto_choice!=0);
    }

void updateval(int qty, float pr)
    {
    sto_quant=qty;
    sto_cost=pr;
    }

void updatestock()
    {
    fstream file("stock.txt", ios::in|ios::out|ios::binary);
    int searchid, found=0;

    if(!file)
    {
	cout<<"\nError opening stock.txt!";
	return;
    }

    char input[10];
    int valid=0;
    while(!valid)
    {
	cout<<"\nEnter Stock ID to Update->";
	cin>>input;
	valid=1;
	for(int i=0; input[i]!='\0'; i++)
	{
	if(!isdigit(input[i]))
	{
	    valid=0;
	    cout<<"Only Numbers Are Allowed Enter Again\n";
	    break;
	}
	}
    }
    searchid=atoi(input);

    while(file.read((char*)this, sizeof(*this)))
    {
	if(sto_id==searchid)
	{
	found=1;
	cout<<"\nCurrent Stock Details:";
	display();

	int choice2;
	valid=0;
	while(!valid)
	{
	    cout<<"\nWhat Do you want to Update?";
	    cout<<"\n1. Quantity";
	    cout<<"\n2. Price";
	    cout<<"\n3. Both Quantity & Price";
	    cout<<"\n4. Name";
	    cout<<"\n5. All (Name, Quantity, Price)";
	    cout<<"\nEnter Your Choice->";
	    cin>>input;
	    valid=1;
	    for(int i=0; input[i]!='\0'; i++)
	    {
	    if(!isdigit(input[i]))
	    {
		valid=0;
		cout<<"Only numbers allowed. Try Again\n";
		break;
	    }
	    }
	    if(valid)
	    {
	    choice2=atoi(input);
	    if(choice2<1||choice2>5)
	    {
		valid=0;
		cout<<"Choice must be between 1-5. Try Again\n";
	    }
	    }
	}
	choice2=atoi(input);

	int newqty;
	float newprice;
	char newname[20];

	switch(choice2)
	{
	    case 1:
	    {
		valid=0;
		while(!valid)
		{
		cout<<"Enter New Quantity->";
		cin>>input;
		valid=1;
		for(int i=0; input[i]!='\0'; i++)
		{
		    if(!isdigit(input[i]))
		    {
		    valid=0;
		    cout<<"Only Digits Allowed. Try Again\n";
		    break;
		    }
		}
		if(valid)
		{
		    newqty=atoi(input);
		    if(newqty<0)
		    {
		    valid=0;
		    cout<<"Quantity cannot be Negative.\n";
		    }
		}
		}
		sto_quant=newqty;
		break;
	    }

	    case 2:
	    {
		valid=0;
		while(!valid) {
		cout<<"Enter New Price->";
		cin>>input;
		valid=1;
		int dotcount=0;
		for(int i=0; input[i]!='\0'; i++)
		{
		    if(!isdigit(input[i])&&input[i]!='.')
		    {
		    valid=0;
		    break;
		    }
		    if(input[i]=='.') dotcount++;
		}
		if(dotcount>1) valid=0;

		if(!valid)
		{
		    cout<<"Invalid price format(Only numbers and One decimal Allowed)\n";
		} else {
		    newprice=atof(input);
		    if(newprice<=0)
		    {
		    valid=0;
		    cout<<"Price must be greater than Zero.\n";
		    }
		}
		}
		sto_cost=newprice;
		break;
	    }

	    case 3:
	    {
		// quantity validation
		valid=0;
		while(!valid)
		{
		cout<<"Enter New Quantity->";
		cin>>input;
		valid=1;
		for(int i=0; input[i]!='\0'; i++)
		{
		    if(!isdigit(input[i]))
		    {
		    valid=0;
		    cout<<"Only Digits Allowed. Try Again\n";
		    break;
		    }
		}
		if(valid) {
		    newqty=atoi(input);
		    if(newqty<0)
		    {
		    valid=0;
		    cout<<"Quantity Cannot be Negative.\n";
		    }
		}
		}

		// price validation
		valid=0;
		while(!valid)
		{
		cout<<"Enter New Price->";
		cin>>input;
		valid=1;
		int dotcount=0;
		for(int i=0; input[i]!='\0'; i++)
		{
		    if(!isdigit(input[i])&&input[i]!='.')
		    {
		    valid=0;
		    break;
		    }
		    if(input[i]=='.') dotcount++;
		}
		if(dotcount>1) valid=0;

		if(!valid)
		{
		    cout<<"Invalid Price Format(Only Numbers and One Decimal Allowed)\n";
		}
		else
		{
		    newprice=atof(input);
		    if(newprice<=0)
		    {
		    valid=0;
		    cout<<"Price must be Greater than Zero.\n";
		    }
		}
		}

		sto_quant=newqty;
		sto_cost=newprice;
		break;
	    }

	    case 4:
	    {
		valid=0;
		while(!valid)
		{
		cout<<"Enter New Name->";
		cin>>newname;
		valid=1;
		for(int i=0; newname[i]!='\0'; i++)
		{
		    if(!isalpha(newname[i]))
		    {
		    valid=0;
		    cout<<"Only Alphabets Allowed. Try Again\n";
		    break;
		    }
		}
		}
		strcpy(sto_name, newname);
		break;
	    }

	    case 5:
	    {
		// name validation
		valid=0;
		while(!valid)
		{
		cout<<"Enter New Name->";
		cin>>newname;
		valid=1;
		for(int i=0; newname[i]!='\0'; i++)
		{
		    if(!isalpha(newname[i]))
		    {
		    valid=0;
		    cout<<"Only Alphabets Allowed. Try Again\n";
		    break;
		    }
		}
		}

		// quantity validation
		valid=0;
		while(!valid)
		{
		cout<<"Enter New Quantity->";
		cin>>input;
		valid=1;
		for(int i=0; input[i]!='\0'; i++) {
		    if(!isdigit(input[i]))
		    {
		    valid=0;
		    cout<<"Only Digits Allowed. Try Again\n";
		    break;
		    }
		}
		if(valid)
		{
		    newqty=atoi(input);
		    if(newqty<0)
		    {
		    valid=0;
		    cout<<"Quantity cannot be Negative.\n";
		    }
		}
		}

		// price validation
		valid=0;
		while(!valid)
		{
		cout<<"Enter New Price->";
		cin>>input;
		valid=1;
		int dotcount=0;
		for(int i=0; input[i]!='\0'; i++)
		{
		    if(!isdigit(input[i])&&input[i]!='.')
		    {
		    valid=0;
		    break;
		    }
		    if(input[i]=='.') dotcount++;
		}
		if(dotcount>1) valid=0;

		if(!valid)
		{
		    cout<<"Invalid Price Format(Only Numbers and One Decimal Allowed)\n";
		}
		else
		{
		    newprice=atof(input);
		    if(newprice<=0)
		    {
		    valid=0;
		    cout<<"Price must be greater than Zero.\n";
		    }
		}
		}

		strcpy(sto_name, newname);
		sto_quant=newqty;
		sto_cost=newprice;
		break;
	    }

	    default:
	    {
		cout<<"\nInvalid Choice(No Update Performed)";
		file.close();
		return;
	    }
	}

	int pos=file.tellg()-sizeof(*this);
	file.seekp(pos);
	file.write((char*)this, sizeof(*this));

	cout<<"\nStock Updated Successfully!";
	break;
	}
    }

    if(!found)
	cout<<"\nStock ID Not Found!";

    file.close();
    getch();
    }

void displayallstocks()
{
    ifstream in("stock.txt", ios::binary);
    if (!in)
    {
	cout<<"\nNo Stock Records Found.";
	getch();
	return;
    }

    cout.setf(ios::left);
    cout<<"\n\n"<< setw(15)<< "Item Name";

    cout.setf(ios::right);
    cout <<setw(10)<<"ID"
	 <<setw(10)<<"Quantity"
	 <<setw(15)<<"Price";

    cout << "\n-------------------------------------------------------------";

    while (in.read((char*)this, sizeof(*this)))
    {
	cout << "\n";
	display();
    }

    in.close();
    getch();
}



void deletestock()
    {
    ifstream in("stock.txt", ios::binary);
    ofstream out("sto_t.txt", ios::binary);
    int searchid, found=0;

    if(!in) {
	cout<<"\nNo Stock Records Found.";
	getch();
	return;
    }

    char input[10];
    int valid=0;
    while(!valid) {
	cout<<"\nEnter Stock ID to Delete->";
	cin>>input;
	valid=1;
	for(int i=0; input[i]!='\0'; i++)
	{
	if(!isdigit(input[i]))                   //yaha tak kara hai
	{
	    valid=0;
	    cout<<"Only digits allowed(Try Again)\n";
	    break;
	}
	}
    }
    searchid=atoi(input);

    while(in.read((char*)this, sizeof(*this)))
    {
	if(sto_id==searchid)
	{
	found=1;
	cout<<"\nDeleting the Following Record:";
	display();
	}
	else
	{
	out.write((char*)this, sizeof(*this));
	}
    }

    in.close();
    out.close();

    remove("stock.txt");
    rename("sto_t.txt", "stock.txt");

    if(found)
	cout<<"\nStock Deleted Successfully!";
    else
	cout<<"\nStock ID Not Found!";
    getch();
    }

void searchstock()
    {
    ifstream in("stock.txt", ios::binary);
    int searchid, found=0;

    if(!in) {
	cout<<"\nError Opening stock.txt!";
	getch();
	return;
    }

    char input[10];
    int valid=0;
    while(!valid)
    {
	cout<<"\nEnter Stock ID to Search->";
	cin>>input;
	valid=1;
	for(int i=0; input[i]!='\0'; i++)
	{
	if(!isdigit(input[i]))
	{
	    valid=0;
	    cout<<"Only Digits Allowed(Try Again)\n";
	    break;
	}
	}
    }
    searchid=atoi(input);

    while(in.read((char*)this, sizeof(*this)))
    {
	if(sto_id==searchid)
	{
	found=1;
	cout<<"\nStock found!";
	display();
	break;
	}
    }

    if(!found)
	cout<<"\nStock id not found!";
    getch();
    in.close();
    }

void displayallbuyer()
    {
    ifstream in("buyer.txt", ios::binary);
    if(!in)
    {
	cout<<"\nNo Buyer Records Found!";
	getch();
	return;
    }

    int buyerid;
    char buyername[30];
    char contact[15];

    cout<<"\n\t\t      --- List Of All Buyers ---";
    cout<<"\n\t\t     Buyer_Id\tName\t\tContact\n";

    while(in.read((char*)&buyerid, sizeof(buyerid)))
    {
	in.read(buyername, sizeof(buyername));
	in.read(contact, sizeof(contact));

	cout<<endl;
	cout<<"\t\t     "<<buyerid;
	cout<<"\t\t"<<buyername;
	cout<<"\t\t"<<contact;
    }
    getch();
    in.close();
    }

void deletebuyer()
{
    ifstream in("buyer.txt", ios::binary);
    ofstream out("sto_t.txt", ios::binary);
    int searchid, found=0;

    if(!in)
    {
	cout<<"\nNo buyer records found!";
	getch();
	return;
    }

    char input[10];
    int valid=0;
    while(!valid)
    {
	cout<<"\nEnter Buyer ID to Delete->";
	cin>>input;
	valid=1;
	for(int i=0; input[i]!='\0'; i++)
	{
	if(!isdigit(input[i]))
	{
	    valid=0;
	    cout<<"Only Numbers Allowed(Try Again)\n";
	    break;
	}
	}
    }
    searchid=atoi(input);

    int buyerid;
    char buyername[30];
    char contact[15];

    while(in.read((char*)&buyerid, sizeof(buyerid)))
    {
	in.read(buyername, sizeof(buyername));
	in.read(contact, sizeof(contact));

	if(buyerid==searchid)
	{
	found=1;
	cout<<"\n Deleting The Following Buyer:";
	cout<<"\nbuyer id->"<<buyerid;
	cout<<"\nname->"<<buyername;
	cout<<"\ncontact->"<<contact<<"\n";
	}
	else
	{
	out.write((char*)&buyerid, sizeof(buyerid));
	out.write(buyername, sizeof(buyername));
	out.write(contact, sizeof(contact));
	}
    }
    getch();
    in.close();
    out.close();

    remove("buyer.txt");
    rename("sto_t.txt", "buyer.txt");

    if(found)
	cout<<"\nBuyer Deleted Successfully!";
    else
	cout<<"\nBuyer Id not Found!";
    getch();
    }

void placeorder()
    {
    ifstream in("stock.txt", ios::binary);
    ofstream out("orders.txt", ios::app|ios::binary);
    ofstream pay("payment.txt", ios::app);
    fstream stockfile("stock.txt", ios::in|ios::out|ios::binary);
    if(!in||!out||!pay||!stockfile)
    {
	cout<<"\nError Accessing Stock, Order, or Payment File!";
	getch();
	return;
    }

    int itemid, orderqty, found=0;
    float total=0;
    char more='y';
    char buyername[30];
    char paymentmode[15], extrainfo[50];
    int orderid=1001;

    // read last order id
    ifstream idin("last_order_id.txt");
    if(idin)
    {
	idin>>orderid;
	idin.close();
	orderid++;
    }
    ofstream idout("last_order_id.txt");
    idout<<orderid;
    idout.close();

    struct date d;
    getdate(&d);
    char day[3], month[3];
    int year=d.da_year;
    itoa(d.da_day, day, 10);
    itoa(d.da_mon, month, 10);

    int buyerid = 1001;
ifstream bidin("last_buyer_id.txt");
if(bidin)
{
    bidin >> buyerid;
    bidin.close();
    buyerid++;
}
ofstream bidout("last_buyer_id.txt");
bidout << buyerid;
bidout.close();

// collect buyer info
ofstream bout("buyer.txt", ios::app | ios::binary);
char contact[15];

cout << "\nBuyer ID-> " << buyerid;

// validate buyer name (only alphabets)
int validname;
do {
    validname = 1;
    cout << "\nEnter Buyer Name -> ";
    cin >> buyername;
    for(int i=0; buyername[i]!='\0'; i++)
    {
    if(!isalpha(buyername[i]))
    {
	validname = 0;
	cout << "Name must contain only Alphabets(Try Again)\n";
	break;
    }
    }
} while(!validname);

// validate contact number (exactly 10 digits)
int valid = 0;
while(!valid)
{
    cout << "Enter Contact Number(10 Digits Only)-> ";
    cin >> contact;
    int len = strlen(contact);
    valid = 1;
    if(len != 10)
    valid = 0;
    else {
    for(int i=0; i<10; i++)
    {
	if(!isdigit(contact[i]))
	{
	valid = 0;
	break;
	}
    }
    }
    if(!valid)
    cout << "Invalid Contact Number! Must be exactly 10 digits(Try Again)\n";
}

// write to buyer file
bout.write((char*)&buyerid, sizeof(buyerid));
bout.write(buyername, sizeof(buyername));
bout.write(contact, sizeof(contact));
bout.close();

cout << "\nbuyer info saved successfully!";

    displayallstocks();

    while(more=='y'||more=='y')
    {
	// validate stock id (only numbers)
	char idinput[10];
	int validid=0;
	do
	{
	cout<<"\nenter stock id to order->";
	cin>>idinput;
	validid=1;
	for(int i=0; idinput[i]!='\0'; i++)
	{
	    if(!isdigit(idinput[i]))
	    {
	    validid=0;
	    cout<<"Invalid Input Only Numbers Are Allowed\n";
	    break;
	    }
	}
	if(validid) itemid=atoi(idinput);
	} while(!validid);

	in.seekg(0, ios::beg);
	stockfile.seekg(0, ios::beg);
	found=0;

	while(stockfile.read((char*)this, sizeof(*this)))
	{
	if(sto_id==itemid)
	{
	    found=1;
	    cout<<"Available Quantity->"<<sto_quant;

	    //validate order quantity (only numbers and positive)
	    char qtyinput[10];
	    int validqty=0;
	    do
	    {
	    cout<<"\nEnter Quantity to Order->";
	    cin>>qtyinput;
	    validqty=1;
	    for(int i=0; qtyinput[i]!='\0'; i++)
	    {
		if(!isdigit(qtyinput[i]))
		{
		validqty=0;
		cout<<"Invalid input only numbers are Allowed(Try Again)\n";
		break;
		}
	    }
	    if(validqty)
	    {
		orderqty=atoi(qtyinput);
		if(orderqty<=0)
		{
		validqty=0;
		cout<<"Quantity must be greater than Zero.\n";
		}
		else if(orderqty>sto_quant)
		{
		validqty=0;
		cout<<"Not Enough Quantity in Stock.\n";
		}
	    }
	    } while(!validqty);

	    float subtotal=sto_cost*orderqty;
	    total+=subtotal;

	    out.write((char*)&orderid, sizeof(orderid));
	    out.write(buyername, sizeof(buyername));
	    out.write((char*)&sto_id, sizeof(sto_id));
	    out.write(sto_name, sizeof(sto_name));
	    out.write((char*)&orderqty, sizeof(orderqty));
	    out.write((char*)&sto_cost, sizeof(sto_cost));

	    out.write(day, sizeof(day));
	    out.write(month, sizeof(month));
	    out.write((char*)&year, sizeof(year));

	    char status[10]="Pending";
	    out.write(status, sizeof(status));

	    sto_quant-=orderqty;
	    int pos=stockfile.tellg()-sizeof(*this);
	    stockfile.seekp(pos, ios::beg);
	    stockfile.write((char*)this, sizeof(*this));

	    cout<<"Item Added to Order Subtotal->"<<subtotal;
	    break;
	}
	}

	if(!found)
	{
	cout<<"\nStock id not found!";
	getch();
	return;
	}

	do
	{
	cout<<"\nDo You Want To Order Another Item? (y/n)->";
	more=getche();
	more=tolower(more);
	if(more!='y'&&more!='n')
	{
	    cout<<"Invalid Input(Please Enter 'y' or 'n' Only)\n";
	}
	} while(more!='y'&&more!='n');
    }

    // payment method selection with validation
    int pchoice;
    char choiceinput[10];
    int validchoice=0;

    do
    {
	cout<<"\nSelect Payment Method:\n1. Cash\n2. Credit Card\n3. UPI\nEnter Choice (1-3)->";
	cin>>choiceinput;
	validchoice=1;
	for(int i=0;choiceinput[i]!='\0';i++)
	{
	if(!isdigit(choiceinput[i]))
	{
	    validchoice=0;
	    cout<<"Invalid Input Only Numbers Are Allowed(Try Again)\n";
	    break;
	}
	}
	if(validchoice)
	{
	pchoice=atoi(choiceinput);
	if(pchoice<1||pchoice>3)
	{
	    validchoice=0;
	    cout<<"Please Enter A Number Between 1 and 3(Try Again)\n";
	}
	}
    } while(!validchoice);

    switch(pchoice)
    {
	case 1:
	strcpy(paymentmode, "Cash");
	strcpy(extrainfo, "-na-");
	break;
	case 2:
	strcpy(paymentmode, "Credit Card");
	// validate card digits (exactly 4 numbers)
	do
	{
	    cout<<"\nEnter Card Number(Only 4 Digits)->";
	    cin>>extrainfo;
	    validchoice=1;
	    if(strlen(extrainfo)!=4)
	    {
	    validchoice=0;
	    cout<<"Please Enter Exactly 4 Digits(Try Again)\n";
	    }
	    else
	    {
	    for(int i=0;i<4;i++)
	    {
		if(!isdigit(extrainfo[i]))
		{
		validchoice=0;
		cout<<"Only Numbers Are Allowed\n";
		break;
		}
	    }
	    }
	} while(!validchoice);
	break;
	case 3:
	strcpy(paymentmode, "UPI");
	// simple upi id validation (contains @)
	do
	{
	    cout<<"\nEnter UPI ID->";
	    cin>>extrainfo;
	    validchoice=0;
	    for(int i=0; extrainfo[i]!='\0'; i++)
	    {
	    if(extrainfo[i]=='@')
	    {
		validchoice=1;
		break;
	    }
	    }
	    if(!validchoice)
	    {
	    cout<<"Invalid UPI ID Must Contain '@' (Try Again)\n";
	    }
	} while(!validchoice);
	break;
    }

    pay<<"Order ID->"<<orderid<<" | Buyer->"<<buyername<<" | Payment->"<<paymentmode
	<<" | Info->"<<extrainfo<<" | Total-> Rs."<<total<<"\n";

    cout<<"\nOrder Placed Successfully! Your Order ID Is->"<<orderid;
    cout<<"\nTotal Bill-> Rs."<<total;
    cout<<"\nPayment Mode->"<<paymentmode;

    in.close();
    out.close();
    pay.close();
    stockfile.close();
    getch();
    }


void updateorderstatus()
    {
    fstream file("orders.txt", ios::in|ios::out|ios::binary);
    if(!file) {
	cout<<"\nNo Orders Found!";
	return;
    }

    int searchorderid, found=0;
    cout<<"\nEnter Order Id To Update Status-> ";
    cin>>searchorderid;

    int oid, sid, qty, year;
    float price;
    char bname[30], sname[20], status[10];
    char day[3], month[3];

    while(!file.eof())
    {
	streampos pos=file.tellg();

	file.read((char*)&oid, sizeof(oid));
	file.read(bname, sizeof(bname));
	file.read((char*)&sid, sizeof(sid));
	file.read(sname, sizeof(sname));
	file.read((char*)&qty, sizeof(qty));
	file.read((char*)&price, sizeof(price));

	file.read(day, sizeof(day));           // read correctly
	file.read(month, sizeof(month));
	file.read((char*)&year, sizeof(year));

	file.read(status, sizeof(status));     // now aligned

	if(file.eof()) break;

	if(oid==searchorderid)
	{
	found=1;
	cout<<"\nOrder Found:\n";
	cout<<"Order id-> "<<oid;
	cout<<"\nBuyer-> "<<bname;
	cout<<"\nStock-> "<<sname;
	cout<<"\nQuantity-> "<<qty;
	cout<<"\nStatus-> "<<status;

	cout<<"\n\nUpdate Status to 'Delivered'? (y/n)-> ";
	char ch;
	cin>>ch;

	if(ch=='y'||ch=='y') {
	    strcpy(status, "Delivered");

	    // seek to the correct position of status
	    file.seekp(pos+sizeof(oid)+sizeof(bname)+sizeof(sid)+sizeof(sname)+
		   sizeof(qty)+sizeof(price)+sizeof(day)+sizeof(month)+sizeof(year));
	    file.write(status, sizeof(status));

	    cout<<"\nStatus Updated to Delivered!";
	}
	break;
	}
    }

    if(!found)
	cout<<"\nOrder ID Not Found!";

    file.close();
    getch();
    }


void checkorderstatus()
    {
    ifstream in("orders.txt", ios::binary);
    if(!in) {
	cout<<"\nNo Order Records Found!";
	getch();
	return;
    }

    int searchid, found=0;
    char input[10];
    int valid=0;

    while(!valid)
    {
	cout<<"\nEnter Order ID to Check Status-> ";
	cin>>input;
	valid=1;
	for(int i=0; input[i]!='\0'; i++)
	{
	if(!isdigit(input[i]))
	{
	    valid=0;
	    cout<<"Only Numbers Allowed(Try Again)\n";
	    break;
	}
	}
    }

    searchid=atoi(input);

    int oid, sid, qty, year;
    float price;
    char bname[30], sname[20], status[10];
    char day[3], month[3];

    while(in.read((char*)&oid, sizeof(oid)))
    {
	in.read(bname, sizeof(bname));
	in.read((char*)&sid, sizeof(sid));
	in.read(sname, sizeof(sname));
	in.read((char*)&qty, sizeof(qty));
	in.read((char*)&price, sizeof(price));

	in.read(day, sizeof(day));           // added  day
	in.read(month, sizeof(month));       // added mon
	in.read((char*)&year, sizeof(year)); // added yr

	in.read(status, sizeof(status));     //status add

	if(oid==searchid)
	{
	found=1;
	cout<<"\nOrder Found:";
	cout<<"\nOrder Id-> "<<oid;
	cout<<"\nBuyer-> "<<bname;
	cout<<"\nStock-> "<<sname;
	cout<<"\nQuantity-> "<<qty;
	cout<<"\nPrice Per unit-> "<<price;
	cout<<"\nDate-> "<<day<<"/"<<month<<"/"<<year;
	cout<<"\nStatus-> "<<status;
	break;
	}
    }

    if(!found)
    {
	cout<<"\nOrder ID Not Found!";
    }

    in.close();
    getch();
    }
void viewallorders_b()
{
    ifstream in("orders.txt", ios::binary);
    if (!in)
    {
    cout << "\nNo Order Records Found!";
    getch();
    return;
    }

    int oid, sid, qty, year;
    char day[3], month[3];
    float price;
    char bname[30], sname[20], status[10];

    cout << "\n\n------------------------------ All Order Display ------------------------------\n";
    cout.setf(ios::left);
    cout << setw(10) << "Order id"
     << setw(15) << "Buyer"
     << setw(15) << "Item"
     << setw(8)  << "Qty"
     << setw(10) << "Price"
     << setw(12) << "Date"
     << setw(10) << "Status" << "\n";

    cout << "-------------------------------------------------------------------------------\n";

    while (in.read((char*)&oid, sizeof(oid)))
    {
    in.read(bname, sizeof(bname));
    in.read((char*)&sid, sizeof(sid));
    in.read(sname, sizeof(sname));
    in.read((char*)&qty, sizeof(qty));
    in.read((char*)&price, sizeof(price));
    in.read(day, sizeof(day));
    in.read(month, sizeof(month));
    in.read((char*)&year, sizeof(year));
    in.read(status, sizeof(status));

    // combine date string
    char date[12];
    strcpy(date, day);
    strcat(date, "/");
    strcat(date, month);
    strcat(date, "/");
    char ystr[6];
    itoa(year, ystr, 10);
    strcat(date, ystr);

    // output formatted row
    cout.setf(ios::left);
    cout << setw(10) << oid
	 << setw(15) << bname
	 << setw(15) << sname;

    cout.setf(ios::right);
    cout << setw(8) << qty;

    cout.setf(ios::fixed);
    cout.precision(2);
    cout << setw(10) << price<<"  ";

    cout.setf(ios::left);
    cout << setw(10) << date
	 << setw(9) << status << "\n";

    }

    in.close();
    getch();
}


void deleteorder()
    {
    ifstream in("orders.txt", ios::binary);
    ofstream out("temp_orders.txt", ios::binary);
    int delid, orderid, stockid, qty, year;
    char day[3], month[3];
    char buyername[30], stockname[20], status[20];
    float price;
    int found=0;

    if(!in)
    {
	cout<<"\nNo Order Records Found!";
	getch();
	return;
    }

    char input[10];
    int valid=0;
    while(!valid)
    {
	cout<<"\nEnter Order ID to Delete->";
	cin>>input;
	valid=1;
	for(int i=0; input[i]!='\0'; i++)
	{
	if(!isdigit(input[i]))
	{
	    valid=0;
	    cout<<"Only Numbers Allowed(Try Again)\n";
	    break;
	}
	}
    }
    delid=atoi(input);

    int oid, sid, qty1;
    float price1;
    char bname[30], sname[20], status1[10];

    while(in.read((char*)&oid, sizeof(oid)))
    {
	in.read(bname, sizeof(bname));
	in.read((char*)&sid, sizeof(sid));
	in.read(sname, sizeof(sname));
	in.read((char*)&qty1, sizeof(qty1));
	in.read((char*)&price1, sizeof(price1));
	in.read(day, sizeof(day));
	in.read(month, sizeof(month));
	in.read((char*)&year, sizeof(year));
	in.read(status1, sizeof(status1));

	if(oid==delid)
	{
	found=1;
	cout<<"\nDeleting Order Id->"<<oid;
	cout<<"\nBuyer->"<<bname;
	cout<<"\nItem->"<<sname;
	cout<<"\nQty->"<<qty;
	cout<<"\nPrice->"<<price;
	cout<<"\nDate->"<<day<<"/"<<month<<"/"<<year;
	cout<<"\nStatus->"<<status;
	cout<<"\n\nOrder Deleted!\n";
	cout<<"\nYour Money Will Be Refunded in 3 business Days";
	}
	else
	{
	out.write((char*)&oid, sizeof(oid));
	out.write(bname, sizeof(bname));
	out.write((char*)&sid, sizeof(sid));
	out.write(sname, sizeof(sname));
	out.write((char*)&qty1, sizeof(qty1));
	out.write((char*)&price1, sizeof(price1));
	out.write(day, sizeof(day));
	out.write(month, sizeof(month));
	out.write((char*)&year, sizeof(year));
	out.write(status1, sizeof(status1));
	}
    }

    in.close();
    out.close();

    remove("orders.txt");
    rename("temp_orders.txt", "orders.txt");

    if(!found)
	cout<<"\nOrder Id Not Found!";
    getch();
    }

void searchorderstatus()
{
    ifstream in("orders.txt", ios::binary);
    if (!in)
    {
    cout << "\nNo Order Records Found!";
    getch();
    return;
    }

    int statuschoice;
    char choiceinput[10];
    int valid = 0;

    while (!valid)
    {
    cout << "\nSearch Orders By Status:";
    cout << "\n1.Pending Orders";
    cout << "\n2.Delivered Orders";
    cout << "\n\nEnter Your Choice(1-2)-> ";
    cin >> choiceinput;

    valid = 1;
    for (int i = 0; choiceinput[i] != '\0'; i++)
    {
	if (!isdigit(choiceinput[i]))
	{
	valid = 0;
	cout << "Only Numbers Allowed(Try Again)\n";
	break;
	}
    }

    if (valid)
    {
	statuschoice = atoi(choiceinput);
	if (statuschoice < 1 || statuschoice > 2)
	{
	valid = 0;
	cout << "Choice must be 1 or 2(Try Again)\n";
	}
    }
    }

    char searchstatus[20];
    if (statuschoice == 1)
    strcpy(searchstatus, "Pending");
    else
    strcpy(searchstatus, "Delivered");

    int oid, sid, qty, year;
    char day[3], month[3];
    float price;
    char bname[30], sname[20], status[10];
    int found = 0;

    cout << "\n\n------------------------ " << searchstatus << " Orders ------------------------";
    cout << "\nOrder ID\tBuyer\t\tItem\t\tQty\tDate\t\tStatus";
    cout << "\n------------------------------------------------------------------";

    while (in.read((char*)&oid, sizeof(oid)))
    {
    in.read(bname, sizeof(bname));
    in.read((char*)&sid, sizeof(sid));
    in.read(sname, sizeof(sname));
    in.read((char*)&qty, sizeof(qty));
    in.read((char*)&price, sizeof(price));
    in.read(day, sizeof(day));
    in.read(month, sizeof(month));
    in.read((char*)&year, sizeof(year));
    in.read(status, sizeof(status));

    if (strcmpi(status, searchstatus) == 0)
    {
	found = 1;
	cout << "\n" << oid << "\t\t" << bname << "\t\t" << sname
	 << "\t" << qty << "\t" << day << "/" << month << "/" << year
	 << "  " << status;
    }
    }

    if (!found)
    {
    cout << "\nNo " << searchstatus << " Orders Found!";
    }

    cout << "\n------------------------------------------------------------------";
    in.close();
    getch();
}

void generatereport()
{
    char choiceinput[10];
    int choice;
    int valid=0;
    while(!valid)
    {
        clrscr();
        cout<<"\n------------------------------- Sales Report Menu -----------------------------";
        cout<<"\n                     1.Press 1 to Generate Full Sales Report";
        cout<<"\n                     2.Press 2 to Generate Sales Report by Specific Date";
        cout<<"\n                     3.Press 3 to Generate Sales Report by Stock Item Name";
        cout<<"\n                     4.Press 4 to Generate Monthly Sales Summary\n";
        cout<<"\n                                Enter Your Choice->";
        cin>>choiceinput;
        valid=1;
        for(int i=0;choiceinput[i]!='\0';i++)
        {
            if(!isdigit(choiceinput[i]))
            {
                valid=0;
                cout<<"Only Digits Allowed(Try Again)\n";
                break;
            }
        }
        if(valid)
        {
            choice=atoi(choiceinput);
            if(choice<1||choice>4)
            {
                valid=0;
                cout<<"Choice Must be Between 1-4(Try Again)\n";
            }
        }
    }

    ifstream in("orders.txt",ios::binary);
    if(!in)
    {
        cout<<"\nNo Order Records Found!";
        getch();
        return;
    }

    char input_day[3],input_month[3],input_stock[20];
    int input_year;
    int filtertype=0;

    if(choice==2)
    {
        valid=0;
        while(!valid)
        {
            cout<<"\nEnter Date(dd mm yyyy)->";
            cin>>input_day>>input_month>>input_year;
            valid=1;
            int day=atoi(input_day);
            if(day<1||day>31)
            {
                valid=0;
                cout<<"Invalid Day (must be 1-31).\n";
                continue;
            }
            int month=atoi(input_month);
            if(month<1||month>12)
            {
                valid=0;
                cout<<"Invalid Month(must be 1-12).\n";
                continue;
            }
            if(input_year<2000||input_year>2100)
            {
                valid=0;
                cout<<"Invalid Year(must be 2000-2100).\n";
                continue;
            }
        }
        filtertype=1;
    }
    else if(choice==3)
    {
        valid=0;
        while(!valid)
        {
            cout<<"\nEnter Stock Item Name->";
            cin>>input_stock;
            valid=1;
            for(int i=0;input_stock[i]!='\0';i++)
            {
                if(!isalpha(input_stock[i]))
                {
                    valid=0;
                    cout<<"Only Alphabets Allowed in Stock Name.\n";
                    break;
                }
            }
        }
        filtertype=2;
    }
    else if(choice==4)
    {
        valid=0;
        while(!valid)
        {
            cout<<"\nEnter Month and Year (mm yyyy)->";
            cin>>input_month>>input_year;
            valid=1;
            int month=atoi(input_month);
            if(month<1||month>12)
            {
                valid=0;
                cout<<"Invalid Month(must be 1-12)\n";
                continue;
            }
            if(input_year<2000||input_year>2100)
            {
                valid=0;
                cout<<"Invalid Year(must be 2000-2100)\n";
                continue;
            }
        }
        filtertype=3;
    }
    else if(choice!=1)
    {
        cout<<"\nInvalid Choice!";
        in.close();
        getch();
        return;
    }

    int oid,sid,qty,year;
    char day[3],month[3];
    float price,totalsale=0;
    char bname[30],sname[20],status[10];
    int found=0;

    cout<<"\n\n\t\t                SALES REPORT";
    cout<<"\n---------------------------------------------------------------";
    cout<<"\nOrderID  ItemName   Qty  UnitPrice   Date       Total";
    cout<<"\n---------------------------------------------------------------";

    while(in.read((char*)&oid,sizeof(oid)))
    {
	in.read(bname,sizeof(bname));
	in.read((char*)&sid,sizeof(sid));
	in.read(sname,sizeof(sname));
	in.read((char*)&qty,sizeof(qty));
	in.read((char*)&price,sizeof(price));
	in.read(day,sizeof(day));
	in.read(month,sizeof(month));
	in.read((char*)&year,sizeof(year));
	in.read(status,sizeof(status));

	if(filtertype==1&&!(strcmp(day,input_day)==0&&strcmp(month,input_month)==0&&year==input_year))
	    continue;
	if(filtertype==2&&stricmp(sname,input_stock)!=0)
	    continue;
	if(filtertype==3&&!(strcmp(month,input_month)==0&&year==input_year))
	    continue;

	float linetotal=qty*price;
	totalsale+=linetotal;
	found=1;

	cout<<"\n"<<setw(7)<<oid<<""
	   <<setw(10)<<sname<<"  "
           <<setw(3)<<qty<<"  "
           <<setw(9)<<setiosflags(ios::fixed)<<setprecision(2)<<price<<"  "
           <<day<<"/"<<month<<"/"<<year<<"  "
           <<setw(9)<<setiosflags(ios::fixed)<<setprecision(2)<<linetotal;
    }

    if(!found)
    {
        cout<<"\nNo Matching Orders Found!";
    }
    else
    {
        cout<<"\n---------------------------------------------------------------";
        if(filtertype==3)
            cout<<"\nTotalSalesForMonth "<<input_month<<"/"<<input_year<<":Rs."
               <<setiosflags(ios::fixed)<<setprecision(2)<<totalsale;
        else
            cout<<"\nTotalSales:Rs."<<setiosflags(ios::fixed)<<setprecision(2)<<totalsale;
        cout<<"\n---------------------------------------------------------------\n";
    }

    in.close();
    getch();
}

};

class seller : public stock
{
public:
int seller_login()
{
    char us_nam[20], pass[20];
    char f_user[20], f_pass[20];
    int found=0;

    cout<<"\n\t               ============= Seller Login ==========\n";
    cout<<"\t                     Enter Username->";
    cin>>us_nam;

    // validate username (only alphanumeric)
    int valid=0;
    while(!valid)
    {
	valid=1;
	for(int i=0; us_nam[i]!='\0'; i++)
	{
	if(!isalnum(us_nam[i]))
	{
	    valid=0;
	    cout<<"Username must be alphanumeric only. Enter again->";
	    cin>>us_nam;
	    break;
	}
	}
    }

    cout<<"\t                     Enter Password->";
    int z;
    for(z=0; z<9; z++)
    {
	pass[z]=getch();
	if(pass[z]==13) break; // enter key
	cout<<"*";
    }
    pass[z]='\0';
    getch();

    ifstream fin("login.txt");
    if(!fin)
    {
	cout<<"\n             login.txt Not Found!";
	getch();
	return 0;
    }

    while(!fin.eof())
    {
	fin>>f_user>>f_pass;
	if(strcmp(us_nam, f_user)==0&&strcmp(pass, f_pass)==0) {
	found=1;
	break;
	}
    }
    fin.close();
    return found;
    }
};

class buyer : public stock
{
public:
    int buyer_login()
    {
    char us_bnam[20], bpass[20];
    char f_buser[20], f_bpass[20];
    int foundb=0;

    cout<<"\n\t               ============= Buyer Login ==========\n";
    cout<<"\t                     Enter Username->";
    cin>>us_bnam;

    // validate username (only alphanumeric)
    int valid=0;
    while(!valid) {
	valid=1;
	for(int i=0; us_bnam[i]!='\0'; i++)
	{
	if(!isalnum(us_bnam[i]))
	{
	    valid=0;
	    cout<<"Username must be alphanumeric only. Enter Again->";
	    cin>>us_bnam;
	    break;
	}
	}
    }

    cout<<"\t                     Enter Password->";
    int j;
    for(j=0; j<8; j++)
    {
	bpass[j]=getch();
	if(bpass[j]==13) break; // enter key
	cout<<"*";
    }
    bpass[j]='\0';


    ifstream fin("loginb.txt");
    if(!fin)
    {
	cout<<"\n             login.txt not found!";
	getch();
	return 0;
    }

    while(!fin.eof())
    {
	fin>>f_buser>>f_bpass;
	if(strcmp(us_bnam,f_buser)==0&&strcmp(bpass,f_bpass)==0)
	{
	foundb=1;
	break;
	}
    }
    fin.close();
    return foundb;
    }

    void menub()
    {
    int choice3;
    char choiceinput[10];
    getch();
    do
    {
	clrscr();
	cout<<"\n\t                             Buyer Menu\n\n";
	cout<<"                           1.Press 1 to Place Order\n";
	cout<<"                           2.Press 2 to Check Order Status\n";
	cout<<"                           3.Press 3 to View All Orders\n";
	cout<<"                           4.Press 4 to Delete Order/Cancel Order\n";
	cout<<"                           5.Press 0 to Exit\n\n";
	cout<<"\n                             Enter Your Choice->";
	cin>>choiceinput;

	// validate menu choice
	int validchoice=1;
	for(int i=0; choiceinput[i]!='\0'; i++)
	{
	if(!isdigit(choiceinput[i]))
	{
	    validchoice=0;
	    break;
	}
	}

	if(validchoice)
	{
	choice3=atoi(choiceinput);
	}
	else
	{
	choice3=-1; //default case
	}

	switch(choice3)
	{
	case 1:
	    {
	    placeorder();
	    break;
	    }
	case 2:
	    {
	    checkorderstatus();
	    break;
	    }
	case 3:
	    {
	    viewallorders_b();
	    break;
	    }
	case 4:
	    {
	    deleteorder();
	    break;
	    }
	case 0:
	    {
	    return;
	    }
	default:
	    {
	    cout<<"\nInvalid Choice";
	    getch();
	    break;
	    }
	}
    } while(choice3!=0);
    }
};

void getdate()
{
    struct date d;
    getdate(&d);

    char day[3], month[3];

    itoa(d.da_day, day, 10);
    itoa(d.da_mon, month, 10);

    cout<<"Date:"<<day<<"/"<<month<<"/"<<d.da_year;
}

int main()
{
    clrscr();
    char log_id[50];
    long int pass;
    char choiceinput[10];
    int choice;
    seller n;
    int h;
    buyer r;

    while(1)
    {
    clrscr();
    cout<<"\n******************** Furniture Stock Management System : Stocker ***************\n";
    cout<<"\t\t\t\t\t\t\t\t"; getdate();
    stock a;
    buyer l;

    cout<<"\n\n\t               ============Welcome User===========";
    cout<<"\n\n\t                    (a).Press 1--Login As Seller";
    cout<<"\n\t                    (b).Press 2--Login As Buyer";
    cout<<"\n\t                    (c).Press 0--Exit program";
    cout<<"\n\n\t                        Enter Choice->";
    cin>>choiceinput;

    // validate main menu choice
    int validchoice=1;
    for(int i=0; choiceinput[i]!='\0'; i++)
    {
	if(!isdigit(choiceinput[i]))
	{
	validchoice=0;
	break;
	}
    }

    if(validchoice)
    {
	choice=atoi(choiceinput);
    }
    else
    {
	choice=-1; // force default case
    }

    switch(choice)
    {
	case 1:
	{
	    if(n.seller_login())
	    {
	    cout<<"\n\t\t          Seller Login Succesfull! Welcome\n";
	    //getch();
	    a.menu();
	    }
	    else
	    {
	    cout<<"\n\n                                 Invalid Login!";
	    getch();
	    }
	    break;
	}
	case 2:
	{
	    if(r.buyer_login())
	    {
	    cout<<"\n\t\t                Buyer Login Success";
	    getch();
	    l.menub();
	    }
	    else
	    {
	    cout<<"\n\t\t             Wrong Entered Id or Password";
	    getch();
	    }
	    break;
	}
	case 0:
	{
	    cout<<"\n\n\n\n\n                           Submitted By->ADITYA KAUSHIK";
	    cout<<"\n                                 Course->BCA\n";
	    cout<<"                         Enrollment No.->120924001";
	    getch();
	    return 0;  // exit the program
	}
	default:
	{
	    cout<<"\n                                Invalid Choice";
	    getch();
	}
    }
    }
    return 0;
}