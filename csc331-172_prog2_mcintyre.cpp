#include <iostream>
#include <string>

using namespace std;

struct personNode
{
  int age;
  string name;
  personNode *link;
};

class linkedListHandler
{
public:
  /**
 * Add Record - Takes two parameters, a string name and an int age
 * ***If the new name is not on the list and the age is valid 18<=age<=45, the name (in uppercase format)
 *    and age will be added such that names are in alphabetical order. 
 * ***When a new name is added, the message “name added” will be displayed. 
 * ***If the name is already on the list or if the age is out of range, 
 *    the name will not be added, and the message “name not added” will be displayed.
 **/
  void addRecord(string name, int age)
  {
    try
    {
      //Make sure age is within the required range before continuing
      if (!ageValidator(age))
      {
        throw "Record not added, age must in the range of 18 and 45 inclusively.";
      }
      //Create a pointer to a new node, reserve memory space for it, and set the data
      personNode *newEntry = new personNode;
      newEntry->age = age;
      newEntry->name = toUpper(name);
      newEntry->link = NULL;

      //If the list is empty, set the head equal to the memory address of the new node
      if (head == NULL)
      {
        head = newEntry;
        print("name added");
        return;
      }
      else
      {
        //If the head is not empty and the new node comes before the head alphabetically, insert new head
        if (head != NULL && !alphabetChecker(head->name, newEntry->name))
        {
          insertNewHead(newEntry);
          print("name added");
          return;
        }
        current = head;
        //If the list is not empty, traverse the node links until we reach the point where we can insert the node
        while (current->link != NULL)
        {
          //If the current name and new name are in alphabetic order
          //AND the current node and next node are not, insert the node after the current node
          if (alphabetChecker(current->name, newEntry->name) && !alphabetChecker(current->link->name, newEntry->name))
          {
            insertAfter(current, newEntry);
            print("name added");
            return;
          }
          else
          {
            //else iterate to the next node
            current = current->link;
          }
        } //end while loop
        //If we hit the end of the list, we create a new tail node
        if (alphabetChecker(current->name, newEntry->name) && current->link == NULL)
        {
          current->link = newEntry;
          print("name added");
          return;
        }
        return;
      }
    }
    //Catch error and print the thrown message
    catch (const char *msg)
    {
      print(msg);
    }
  };
  /**
   * Takes a node and inserts it as the new head of the linked list
   * */
  void insertNewHead(personNode *insertNode)
  {
    insertNode->link = head;
    head = insertNode;
  }
  /**
 * Inserts personNode param2 after param1
 **/
  void insertAfter(personNode *staticNode, personNode *afterNode)
  {
    afterNode->link = staticNode->link;
    staticNode->link = afterNode;
  }
  /**
   * Delete – To delete a name and age from the list, enter a transaction in the form of “D”, space, name. 
   * For example: “D Ling”. If the name is not on the list, the message “name not found” will be displayed. 
   * If the name is on the list, the name and age will be removed and the message “name deleted” will be displayed.
   **/
  void deleteRecord(string name)
  {

    //Capitalize name so we can match the style of our list, and more easily compare characters
    name = toUpper(name);

    //If our delete name matches the head node, set the next node as the head node and exit the function
    if (head->name.compare(name) == 0)
    {
      current = head;
      head = head->link;
      print("name deleted - Head node");
      //Delete the old head to deallocate the orphaned node
      delete current;
      return;
    }

    //New pointer to keep track of the previous node, to delete or
    //we can reassign its link to reference the node after our deleted node
    personNode *lastNode = NULL;
    lastNode = head;
    current = head->link;

    while (current->link != NULL)
    {
      //If the name matches, set the last nodes link to the link of the current node
      if (current->name.compare(name) == 0)
      {
        lastNode->link = current->link;
        print("name deleted - While Loop");
        delete current;
        return;
      }
      //If the name doesn't match set the last node to our current node
      //and iterate current to the next node
      else
      {
        lastNode = current;
        current = current->link;
      }
    } //end of while loop
    //If we get here and the last node matches the name for deletion, set lastNode->link to null
    if (current->name.compare(name) == 0)
    {
      lastNode->link = NULL;
      print("name deleted - Tail Node");
      delete current;
      return;
    }
    print("name not found");
    return;
  };
  /**
   * List – To display the names in the list, enter a transaction in the form of “L”. 
   * Each name in the list will be displayed with the respective age on a line by itself.
   **/
  void listRecords()
  {
    current = head;
    while (current != NULL)
    {
      printRecord(current);
      current = current->link;
    }
    cout << endl;
  }
  /**
   * Upper casing utility function 
   **/
  string toUpper(string text)
  {
    for (int i = 0; i < text.length(); i++)
    {
      text[i] = toupper(text[i]);
    }
    return text;
  }
  /**
   * Lower caseing utility function
  **/
  string toLower(string text)
  {
    for (int i = 0; i < text.length(); i++)
    {
      text[i] = tolower(text[i]);
    }
    return text;
  }
  /**
   * Age Validating utility function
   * Returns true if 18<=Age<=45 
   **/
  bool ageValidator(int age)
  {
    if (age < 18 || age > 45)
      return false;
    return true;
  }
  /**
   * Prints the record in the form Abcd
   * */
  void printRecord(personNode *node)
  {
    string formattedName;
    formattedName = toLower(node->name);
    formattedName[0] = toupper(formattedName[0]);
    cout << formattedName << " " << node->age << endl;
  }
  /**
   * Boolean Alphabetizing Check
   * Takes two strings, returns true if string 1 is before string 2 alphabetically
   * Throws an error if a duplicate entry is being added
   **/
  bool alphabetChecker(string first, string second)
  {
    int answer = first.compare(second);
    //If the names are identical throw an error so we don't add a duplicate name
    if (answer == 0)
      throw "Name already in list, name not added.";
    //compare will return a negative integer if the first parameter is alphabetically before the second
    else if (answer <= -1)
      return true;
    //else if it is a positive integer, the two inputs are not in alphabetical order
    else
      return false;
  }

  /**
   * Print utility function
   * */
  void print(string text)
  {
    cout << text << endl;
  }

  //Constructor
  linkedListHandler()
  {
    head = NULL;
    current = head;
  }

private:
  personNode *head, *current;
};

int main()
{
  char action;
  string name;
  int age;
  linkedListHandler listHandler;

  while (toupper(action) != 'Q')
  {
    cout << "Please enter a transaction: ";
    cin >> action;

    switch (toupper(action))
    {
    case ('L'):
      listHandler.listRecords();
      break;
    case ('A'):
      cin >> name >> age;
      listHandler.addRecord(name, age);
      break;
    case ('D'):
      cin >> name;
      listHandler.deleteRecord(name);
      break;
    }
  }
  return 0;
}

/**Extra Work
 * add another pointer to every node that will let you traverse the linked list backwards and forwards
 *   pointer to first node and last node
 * Trees - binary search tree where each node has two pointers, one to left and one to right
 *   log complexity searching
 * Recursion to search - see if a name exists before you delete it
 *   Base case - find a match or hit end of linked list
 *   Call the recursive function with the head, finds it or hits end, else call the function again with head->link
 * */
