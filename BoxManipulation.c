#include <stdio.h> // provides printf and scanf 
#include <ctype.h> // contains functions for manipulating characters (isalpha isdigit islower isupper tolower toupper)
#include <string.h>//for strcmp
#include <stdlib.h>// for malloc 

/**
 * Struct Box.
*/
struct box{
    float length;
    float width;
    float height;
    float x;
    float y;
    float z;
    char* color;
};

//
/**
 * Box pointer passed in. Volume is calculated as length.
 * @param struct box *, pointer to a struct box is accepted.
*/
float volume(struct box *b){    
    float vol = (*b).length * (b -> width) * (*b).height; //(input -> width) is another way of calling the width from the box pointer
    return vol; 
}

/**
 * Capitalize an array of characters (String in other languages).
*/
void capitalize(char a[]){ 
    for(int i = 0; a[i] != '\0'; i++){  //at the end of string is where \0 is at 
        a[i] = toupper(a[i]);           //Overwriting the character to uppercase 
    }
}

/**
 * Main Method.
*/
int main(void){
    printf("\n");
    //allocate storage for 100 boxes in the array
    struct box boxes[100];       //Array of boxes Restricted to 100 elements.
    struct box *pointBoxes[100]; //Array (datatype struct box pointers) to store each boxes' pointer
    
    int control = 1;//to make in
    while(control == 1){ //while loop for switch statement 
        //Main Menu
        printf("*** Please select from the Menu below ***\n"); 
        printf("\t1) Create New Boxes\n");
        printf("\t2) View a Box's Properties\n");
        printf("\t3) Find the Volume of a box\n");
        printf("\t4) Compare which Box has a Higher Volume\n");
        printf("\t5) Mutate a box\n");
        printf("\t6) Exit (Terminate the Program)\n");
        int choice; //switch control variable (1-6)
        // int index = 0; //to ensure no more than 100 box objects are created 
        int totalBoxes = 0;
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                if(totalBoxes < 100){ //100 spots are allocated for the boxes array, To restrict and cannot make more. 
                    printf("How many boxes would you like to add?\n");
                    int numBoxes;
                    scanf("%d", &numBoxes);
                    for (int i = totalBoxes; i < totalBoxes + numBoxes; i++) {
                        int increment = 1;
                        printf("Enter length of Box %d: ", totalBoxes+increment);
                        float len;
                        scanf("%f", &len);

                        printf("Enter width of Box %d: ", totalBoxes+increment);
                        float wid;
                        scanf("%f", &wid);

                        printf("Enter height of Box %d: ", totalBoxes+increment);
                        float ht;
                        scanf("%f", &ht);

                        printf("Enter the color of Box %d: ", totalBoxes+increment);
                        char clr[20];
                        scanf("%s", &clr);
                        
                        increment++;
                        boxes[i].length = len; //set the first box's length
                        boxes[i].width = wid;
                        boxes[i].height = ht;
                        boxes[i].color = malloc(strlen(clr)+1); //allocate memory for the color string
                        strcpy(boxes[i].color, clr);
                        pointBoxes[i] = &boxes[i]; //store the address of each box in the pointBoxes array
                        printf("\t\t*Box %d Dimensions--->\t\tlength: %.1f\twidth: %.1f\theight: %.1f\tcolor: %s\n\n", 
                                i+1, boxes[i].length, boxes[i].width, boxes[i].height, boxes[i].color);
                    }
                    totalBoxes = totalBoxes + numBoxes; //increase the number of boxes
                    // index = index + numBoxes + 1; //increment the (global) index so if user adds new boxes 2 separate times, each box is kept track of
                    break;                        
                }

            
            case 2://View a Box's properties
                printf("\n");
                float loop = 10;
                while(loop == 10){
                    printf("Enter what box number you would like to view.\nBox #: ");
                    int bNum;
                    scanf("%d", &bNum);
                    bNum = bNum - 1;
                    printf("\t\t*Box %d Dimensions--->\t\tlength: %.1f\twidth: %.1f\theight: %.1f\tcolor: %s\n\n", 
                            bNum+1, boxes[bNum].length, boxes[bNum].width, boxes[bNum].height, boxes[bNum].color);

                    printf("View another box(enter yes) or return to menu(enter no): ");
                    char esc[10];
                    scanf("%9s", &esc);
                    capitalize(esc);
                    while(strcmp(esc, "YES") != 0 || strcmp(esc, "NO") != 0){
                        printf("please enter yes/no: ");
                        scanf("%9s", &esc);
                        capitalize(esc);
                        if(strcmp(esc, "YES") == 0){ //strcmp return 0 if the strings are equal
                            loop = 10;//continue to loop
                        }
                        else if(strcmp(esc, "NO") == 0){ //strcmp return 0 if the strings are equal
                            loop = 0; //breaks requirement of case method loop
                            break; //break out the yes || no while loop
                        }
                    
                    }
                }
                break; //break out case 2

            case 3://Find the Volume of a box
                printf("Enter the Box# you'd like the volume for: ");
                int bnum;
                scanf("%d", &bnum);
                bnum = bnum - 1;
                printf("Volume: %.1f\n", volume(pointBoxes[bnum]));
                break;

            case 4: //Find which box has higher volume among 2
                printf("Enter two box numbers, seperated by a space, to see which box has a higher volume: ");
                int a, b;
                scanf("%d %d", &a, &b);
                float v1 = volume(pointBoxes[a-1]);
                float v2 = volume(pointBoxes[b-1]);
                
                if(v1 > v2){
                    printf("Box#%d has a greater volume than Box#%d\n", a, b);
                }
                else if(v1 < v2){
                    printf("Box#%d has a greater volume than Box#%d\n", b, a);
                }
                else if(v1 == v2){
                    printf("Both Boxes %d %d have equivalent volume: %.1f\n", a, b, v1);
                }
                printf("\tVolume of Box#%d is %.1f\n", a, v1);
                printf("\tVolume of Box#%d is %.1f\n", b, v2);
                break;
                
            case 5://Mutate a Box selected by the user.
                printf("");
                int loops = 1;
                while(loops == 1){
                    printf("\nEnter what Box# you would like to modify: ");
                    int position;
                    scanf("%d", &position);
                    position = position - 1; //makes it cleaner to reference the array index
                    if(position+1 > 0 && position <= totalBoxes){//if user doesn't enter negative number and a box# greater than the number of boxes they've added
                        printf("Enter the number to do any of the following modifications to Box%d:\n", position+1);
                        printf("\t1) Change the Length of the Box\n");
                        printf("\t2) Change the Width of the Box\n");
                        printf("\t3) Change the Height of the Box\n");
                        printf("\t4) Change the Color of the Box\n");
                        printf("\t5) Finished all edits, exit back to Main Menu\n");
                    
                        int control;
                        scanf("%d", &control);
                        switch(control){
                            case 1:
                                printf("Current Length of Box%d is %.1f\n", position+1, boxes[position].length);
                                printf("Enter the New Length: ");
                                float newLength;
                                scanf("%f", &newLength); //scan the new user inputted new length
                                boxes[position].length = newLength; //set the box's new length
                                break;
                            case 2:
                                printf("Current Width of Box%d is %.1f\n", position+1, boxes[position].width);
                                printf("Enter the New Width: ");
                                float newWidth;
                                scanf("%f", &newWidth);
                                boxes[position].width = newWidth;
                                break;
                            case 3:
                                printf("Current Height of Box%d is %.1f\n", position+1, boxes[position].height);
                                printf("Enter the New Height: ");
                                float newHeight;
                                scanf("%f", &newHeight);
                                boxes[position].height = newHeight;
                                break;
                            case 4:
                                printf("Current Color of Box%d is %s\n", position+1, boxes[position].color);
                                printf("Enter the New Color: ");
                                char newColor[20];
                                scanf("%s", &newColor); //scan in the user input newColor
                                boxes[position].color = malloc(strlen(newColor)+1); //allocate memory for the color string
                                strcpy(boxes[position].color, newColor); //use string copy to copy over the new color to the Box
                                break;
                            case 5:
                                loops = 0; //break requirement loops == 1
                                break;
                            default:
                                printf("Invalid option. Try again.");
                        }//nested switch
                    }//end if statement
                    else{
                        printf("Please enter a new Box#. Click any key.");
                        scanf("%d", &position);
                    }
                }//while 
                break;//case 5 break
            
            case 6://Terminate the program
                control = 0; //does not meet requirement of control = 1
                 break;
            
            default:
                printf("Invalid option. Try again.");
            }//end main menu switch
    }//end main while
}//end main 
