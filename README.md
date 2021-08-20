# disease_management_program

This code was written with visual studio 2019 on windows.

instroduction
- Binary Search Tree, Queue, and Maxheap are used.
- Receive patient information and commands from the .txt file and store the information according to each patient's region
- Queue, BST, and maxheap all respond to pop operation.
  -> It is QPOP that moves patient information from Queue to BST.
  -> Moving from BST to Maxheap is BPOP.
- Bst includes locdtion and patient BST.
  -> The location BST has the root address of the patient BST that matches the region to connect the two BSTs.

PatientBST
- It starts at the Root and repeats until cur has the same name or cur becomes NULL.
- When cur becomes NULL, prev becomes the parent of the insertion position.
- If the root is NULL, it is stored in the root.
- Otherwise, it is compared with the name of prev.
  -> If the name to be inserted is large, it is inserted to the right of prev, and if it is small, it is inserted to the left of prev.
  
  
Search
- Compare cur's name with the name you want to find.
  -> If the name of cur is larger, it moves to the left of cur, otherwise it moves to the right of cur.
- Repeat this operation until cur becomes NULL.
  -> If the name of cur and the name to be searched are the same in the middle, it prints and ends.


Delete
- cur starts at the root and goes down repeatedly until the name to be deleted is found or NULL is reached.
- If the name of cur is greater than the searched name, cur becomes cur's left, and if it is smaller than cur's name, cur becomes cur's right.
- If cur and the search name are the same, cur becomes a node to be deleted, and the deletion method is different depending on how many child it has.
- There are cases where cur is Root and cases where it is not.
    1. In case of root
      1-1. Initializes NULL at the parent's cur position and deletes it.
    2. If it is not the root, it connects cur's parent and cur's child.
      2-1. If there is no child, NULL is connected, and when there is one child, the child and parent are connected.
      2-2. If there are two child, use pprev, prev, and c to raise the largest of cur's left child.
 - How to find the largest name of cur's left child
    1. Starting from the right child of cur's left child, we keep checking for the right child until c is NULL.
    2. If c becomes NULL, prev becomes the largest child, so instead of cur, prev is linked with the parent.
    3. NULL is inserted in place of the original prev.
    
 
Print
- The pre, in post print is implemented using recursion for each traversal method.
- PRINT_LEVEL
    1. Repeat until cur is NULL.
    2. It starts by printing the root.
    3. If there is cur's left, push it to the queue.
    4. If there is a right, push it to the queue after left.
    5. cur stores and pops the first element of the queue.


LocationBST
- In the constructor, the root, Gwangju, is initialized first.
- In Insert_Location, reset Daegu to the left of Gwangju, Seoul to the right of Gwangju, Busan to the left of Daegu, Daejeon to the right of Daegu, Incheon to the left of Seoul, and Ulsan to the right of Seoul.


insert_Patient
- cur starts at the root and searches until the location of the received patient is equal to the location of the locationNode.
- If cur=NULL, the iteration ends.
- If the same region is found before cur is NULL, node information is sent to the BST insert of that region.
- Place according to patient's location and alphabetical order of locationnode when iterating
    1. If locationnode is large, cur=left child of cur
    2. If locationnode is small, cur=right child of cur
    

Search, Delete
- If there is a matching patient name in each Location node, return 1 and exit
- If there is no matching patient name, Gwangju, Daegu, Busan, Seoul, Ulsan, Incheon, and Daejeon are operated in order.
- If there is no operation in all regions, return 0 and exit.


LocationHeap
- insert
  1. If you add a local patient in the heap node
    -> After incrementing the count of the node by 1, it is rearranged to fit the size.
  2. If you add a local patient that is not in the heap node
    2-1. create a new node
    2-2. Compare the values and insert a new node at the appropriate location.
   

Manager
- run
  1. Receive command.txt and use strtok to check by dividing the string based on “ “. 
  2. It sees the characters coming into cmd and calls the appropriate command.
  3. If it succeeds, it outputs success, and if it fails, it outputs an error.
  
- LOAD, ADD
  1. It takes a string and divides it by " ".
  2. After setting the appropriate information for p, p is inserted into the queue.
  3. If there is an error when opening the file or if it has been loaded before, an error message is displayed.
  4. ADD receives patient information and inserts it into the queue by the same operation as LOAD.
  
- PRINT
  1. PRINT proceeds by dividing the string received as an argument based on “ “.
    1-1. If the first divided character is B, it is BST output.
    1-2. If PRE, IN, POST, and LEVEL come after dividing once more, output according to each traversal method.
    1-3. If any other character is encountered, an error is output.
  2. An error is output even if the argument is insufficient.
  3. If the first divided letter is H
    3-1. If the heap size is 0, an error message is output.
    3-2. If it is not 0, the Heap is output.
  4. If it is not H, an error message is output.

