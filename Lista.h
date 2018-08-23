#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>

using namespace std;



//single element
struct paragraph {
    string s;
    int id;
    paragraph *next;    // pointer to next element
    paragraph(int ID)          
	{
		next = 0;       
		id = ID;
		cout<<"String "<<id<<" has been created"<<endl;
	}

	~paragraph()
	{
		cout<<"String "<<id<<" has been destroyed"<<endl;
	}

};

//base of elements
struct lista {

    paragraph *head;  // first element (Head)
	int ID;

    lista()
	{
		head = 0;   
		ID = 1;
	};

	~lista()
	{
		delete(head);
	}
//show all elements
void show()
{
    // Head ref
    paragraph *line = head;

    // itteration
    while (line)
    {
		cout<<"string: "<<line->s<<", ID: "<<line->id<<endl;
        line=line->next;
    }
};
//show all specificated elements
void show(string _s)
{
    paragraph *line = head;
	int counter=0;

    while (line)
    {
		if(_s == line->s) 
		{
		cout<<"string: "<<line->s<<", ID: "<<line->id<<endl;
		counter++;
		}
        line=line->next;
		
    }
	if(0 == counter) cout<<"There is no any elements, with string like that"<<endl;
};
//remove specificated elements
void remove(string _s)
	{
	// pointers
    paragraph *line = head;
	paragraph *piervious = line;

    // finding elements with specificated string
	int i = 0;
    while (line)
    {
		//first element
		if(_s==line->s && 0 == i)
		{
			if(line->next) head = line->next;
			else head = 0;
		}

		//next elements
		if(_s==line->s && 0 < i)
		{
			if(line->next) piervious->next = line->next;
			else piervious->next = 0;
		}

		//incrementaion and transition
		i++;
		piervious=line;
        line=line->next;
    }
}

void remove(int _id)
	{
	// pointers
    paragraph *line = head;
	bool done = false;
	paragraph *piervious = line;

    // finding elements with specificated string
	int i = 0;
    while (line)
    {
		//first element
		if(_id==line->id && 0 == i)
		{
			//help = line;
			if(line->next) head = line->next;
			else head = 0;
			done = true;
		}

		//next elements
		if(_id==line->id && 0 < i)
		{
			//help=line;
			if(line->next) piervious->next = line->next;
			else piervious->next = 0;
			done = true;
		}

		if(done) break;

		//incrementaion and transition
		i++;
		piervious=line;
        line=line->next;
    }
	if(done) cout<<"Done"<<endl;
	else cout<<"wrond id number"<<endl;
}

//this function is createing new item
void puch(string _s)
{
    paragraph *create = new paragraph(ID);    // new element
	ID++;
    // fill new string
    create->s = _s;

	// is  it first?
    if (head==0) 
    {
        head = create;
		cout<<"The head is done"<<endl;
    }

    else
    {
        paragraph *p_help = head;

        while (p_help->next)
        {
            p_help = p_help->next;
        }

        p_help->next = create;  
        create->next = 0;     

		cout<<"next element is done"<<endl;
    }
};
//delete last element
void pop()
{
	

	if(0<Getsize())
	{
		// pointer
    paragraph *actual = head;
	paragraph *next = actual->next;
    // finding elements with specificated string
    while (actual)
    {
		//last element
		
			//help=line;
			if(next->next)
			{
				//transition
				cout<<"next"<<endl;
				actual = actual->next;
				next=next->next;
			}
			else {
				actual->next = NULL;
				cout<<"Last element is deleting "<<endl;
				break;
			}
		
	 }
	}//if
	else cout<<"0 elements"<<endl;

}
//show size of list
void size()
{
	 // pointer
    paragraph *line = head;
	// variable int
	int count = 0;

   
    while (line)
    {
		count++;
        line=line->next;
    }

	if(0 == count) cout<<"There is not any elements !! "<<endl;
	else if (1 == count) cout<<"There is a one element "<<endl;
	else cout<<"There are "<<count<<" elements "<<endl;
}
//switching strings form one structure to other structure. Finaly strings are sorted.
void sort()
{
	 // pointers
    paragraph *line = head;
	string  s_help;
	int size = Getsize();
	for(int i=0; i<size; i++)
	{
			for(int j=0;j<(size-1);j++)
			{
				if((line->s) > (line->next->s))
				{
					s_help = line->s;
					line->s = line->next->s;
					line->next->s = s_help;
				}
				line = line->next;
			}
			line=head;
	}
	cout<<"sorted "<<endl;
}
//reset queue of ID
void resetID()
{
	ID = 1;

	paragraph *Line = head;

	while(Line)
	{
		Line->id = ID;
		ID++;
		Line=Line->next;
	}
	cout<<"Id are reseted"<<endl;
	show();

}
//return specificated string
string GetString(int n)
{
	paragraph *Line = head;

	if(Line)
	{
	for(int i=0; i<(n-1); i++) 
	{
		if(Line->next)	Line = Line->next;
		else 
		{
			cout<<"not enought elements"<<endl;
			return " ";
		}
	}
	}
	else return " ";

	return Line->s;
}

//if there is an element, function will return first id of element, else will return 0
int FindElement(string _s)
{
	 // pointer
    paragraph *line = head;
	// variable int
	int count = 0;

   
    while (line)
    {
		if(line->s == _s) return line->id;
        line=line->next;
    }
	return 0;
}

//if is there an element, function will return true, else will return false
bool IsThereElement(string _s)
{
	// pointer
    paragraph *line = head;
	// variable int
	int count = 0;

   
    while (line)
    {
		if(line->s == _s) return true;
        line=line->next;
    }
	return false;
}

//return size of list
int Getsize()
{
	paragraph *line = head;
	int count = 0;
	while (line)
    {
		count++;
        line=line->next;
    }
	return count;
}

};