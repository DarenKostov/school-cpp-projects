/*

   Daren Kostov
   Zuul
   11/01/2022

resources used:
https://www.geeksforgeeks.org/getline-string-c/
https://stackoverflow.com/questions/213761/what-are-some-uses-of-template-template-parameters
https://stackoverflow.com/questions/29360555/c-passing-an-array-directly-into-a-function-without-initializing-it-first
https://stackoverflow.com/questions/4000358/is-possible-to-get-automatic-cast-from-user-defined-type-to-stdstring-using-co
https://en.cppreference.com/w/cpp/chrono/c/time
https://cplusplus.com/forum/beginner/4639/
https://www.geeksforgeeks.org/typedef-in-cpp/
https://cplusplus.com/doc/tutorial/files/
https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
https://stackoverflow.com/questions/20193464/how-to-get-the-exit-code-of-program-invoked-by-system-call

https://superuser.com/questions/186520/colors-in-cygwin-being-displayed-as-raw-ansi-codes

*/
#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>

// #include "./parser.h"

#ifndef q
#define q
#include "./text.h"
#include "./globalVarsNFuns.h"
#include "./command.h"
#include "./parser.h"

//slot in inventory
#include "./path.h"
//item
#include "./file.h"
//inventory
#include "./memory.h"
//room
#include "./folder.h"
//building
#include "./computer.h"

//location 2
#include "./ipadress.h"

//street adress of a building
// #include "./localipadress.h"

//longitude and latidude of a city?? TBD
// #include "./globalipadress.h"

//city? TBD
// #include "./network.h"

// std::ostream &operator <<(std::ostream&, Text&);

   
#endif


//==consts

//text colors characters/commands use
//all characters talking are bold and bright
//all characters thinking are bright
//all command output/misc is normal color

//=me!

//cyan fg, black bg, bold
const Text Daren_talking="\033[36;1m";
//bright cyan fg, black bg
const Text Daren_thinking="\033[96m";

//=you, the player

//green fg, black bg, bold
const Text Player_talking="\033[32;1m";
//bright green fg, black bg
const Text Player_thinking="\033[92m";

//=your boss in the game plot

//green fg, black bg, bold
const Text Boss_talking="\033[33;1m";
//bright green fg, black bg
const Text Boss_thinking="\033[93m";

//=some admin in the system you are infiltrating

//green fg, black bg, bold
const Text Admin_talking="\033[31;1m";
//bright green fg, black bg
const Text Admin_thinking="\033[91m";



using namespace std;



//edits a file with the editor given, returns false when unsucessfull
bool editFile(Text, File);

//prompts the user to press enter to continue
void endSegment(bool);


//commands from user

//typedef function pointer 
typedef bool (*Exec)(Computer&);


bool execCD(Computer&);
bool execLS(Computer&);
bool execCAT(Computer&);
bool execTOUCH(Computer&);
bool execRM(Computer&);
bool execMKDIR(Computer&);
bool execPWD(Computer&);
bool execCLEAR(Computer&);
bool execGREP(Computer&);
bool execCOPY(Computer&);
bool execPASTE(Computer&);
bool execCOPYBUFFER(Computer&);
bool execVI(Computer&);
bool execVIM(Computer&);
bool execNEOVIM(Computer&);
bool execHELIX(Computer&);
bool execEMACS(Computer&);
bool execNANO(Computer&);
bool execMICRO(Computer&);
bool execEDITOR(Computer&);
bool execFREE(Computer&);
bool execTREE(Computer&);
bool execSSH(Computer&);
bool execEXIT(Computer&);
bool execHELP(Computer&);
bool execMAN(Computer&);


int main(int argc, char *argv[]){

   //storing this because on windows its .exe, on linux is .elf, and for macos.... idk
   Text thisFile = argv[0];

   //is this an ssh

   bool isThisAnSSH=false;
   if(argc>1){
      if(Text(argv[1])=="yes")
         isThisAnSSH = true;
   }
   
   // if(isThisAnSSH)
   //    exit(34);

   // int a=system((thisFile+" yes").val());

   // if(WEXITSTATUS(a)==34)
   //    cout << "works\n";
   
   //change seed
   srand(time(0));

   bool isColorOn=true;
   
   //array of function pointers
   Exec exec[]={
      execCAT,
      execLS,
      execCD,
      execTOUCH,
      execRM,
      execMKDIR,
      execPWD,
      execCLEAR,
      execGREP,
      execCOPY,
      execPASTE,
      execCOPYBUFFER,
      execVI,
      execVIM,
      execNEOVIM,
      execHELIX,
      execEMACS,
      execNANO,
      execMICRO,
      execEDITOR,
      execFREE,
      execTREE,
      execSSH,
      execHELP,
      execMAN,
   };
   //an array of what these functions actually are
   Text execDef[]={
      "cat",
      "ls",
      "cd",
      "touch",
      "rm",
      "mkdir",
      "pwd",
      "clear",
      "grep",
      "copy",
      "paste",
      "copybuffer",
      "vi",
      "vim",
      "neovim",
      "helix",
      "emacs",
      "nano",
      "micro",
      "editor",
      "free",
      "tree",
      "ssh",
      "help",
      "man",
   };
   


   
   slowtalk(isColorOn, "Welcome to Zuul", Daren_talking);
   fasttalk(isColorOn, "\n\n  This project is not ready", Daren_thinking);
   // slowtalk(isColorOn, ".....", Daren_thinking, 50);
   fasttalk(isColorOn, "\n\n  Should be ready soon thought.\n\n", Daren_thinking);
   fasttalk(isColorOn, "\n\n  ...I hope...\n\n", Daren_thinking);
   
   
   fasttalk(isColorOn, "\n\nPerhaps Ill never finish it...\nthis is a working demo at least\n\n", Daren_thinking);
   
   // while(true)
      endSegment(isColorOn);
      fasttalk(false, "\nFirst off, do you see the text above as cyan OR white with some weird \"\\033[36;1m\" at the begining of every line?\n", Daren_thinking);
   fasttalk(false, "If you dont see color and are using cygwin you can go over here:\n", Daren_thinking);
   fasttalk(false, "https://superuser.com/questions/186520/colors-in-cygwin-being-displayed-as-raw-ansi-codes\n", Daren_thinking);
   fasttalk(false, "\n....or you can disable color :(\n", Daren_thinking);
   fasttalk(false, "Disable color? [N/y]", Daren_talking);


   //disables color if needed  
   {
      char color[99];
      cin.getline(color, 99);
      switch(color[0])
         case 'y':
         case 'Y':
            isColorOn=false;
   }

   fasttalk(isColorOn, "\nAlso make sure you're playing full screen or that the text doesnt wrap\n", Daren_thinking);
   
   endSegment(isColorOn);
   
   fasttalk(isColorOn, "Before the game begins I want to apologize for this being the most broken \"operating system\" out there.\n", Daren_thinking);
   fasttalk(isColorOn, "Why is this in /sys? Why is this in /etc? That's not how a .conf file looks like!\n", Daren_thinking);
   fasttalk(isColorOn, "To counter all of this I'm just gonna say that this is an oversimplified system\n\n", Daren_thinking);
   
   fasttalk(isColorOn, "When do I give the full path? When do I not? You gotta look at the code closely to understand.\n", Daren_thinking);
   fasttalk(isColorOn, "And because of this I strongly recomend to go in the folder you have bussiness with and do your actions there.\n\n", Daren_thinking);


   fasttalk(isColorOn, "Basicaly when wanting to GET or DELETE a file you either put its name (has to be in working directory)\n", Daren_thinking);
   fasttalk(isColorOn, "or give full path to it, you cannot give path relative to the working directory.\n\n", Daren_thinking);
   
   fasttalk(isColorOn, "But when you CREATE a file you can also use a path relative to the working directory.\n", Daren_thinking);
   fasttalk(isColorOn, "...for the most part...\n\n", Daren_thinking);
   fasttalk(isColorOn, "And once again because of that I strongly recomend to go in the folder you have bussiness with and do your actions there.\n", Daren_thinking);
   fasttalk(isColorOn, "Oh and btw you cannot chain \"../\" with other stuff, it has to be on its own and only works when changing working directory\n\n", Daren_thinking);
   
   fasttalk(isColorOn, "Don't worry all basic zuul functionality works as intended, its just when you try to use the extra functionality.\n", Daren_thinking);
   
   endSegment(isColorOn);
      
   fasttalk(isColorOn, "At the end of the day I tried making something like Unix (more like Linux since I use Linux)\n\n", Daren_thinking);
   
   fasttalk(isColorOn, "What from zuul is what here:\n", Daren_thinking);
   fasttalk(isColorOn, "(keep in mind not everything is 1 to 1)\n", Daren_thinking);
   fasttalk(isColorOn, "=Commands:\n", Daren_thinking);
   fasttalk(isColorOn, "go = cd\n", Daren_thinking);
   fasttalk(isColorOn, "lookaround/(describe the room) = ls, du\n", Daren_thinking);
   fasttalk(isColorOn, "take = copy\n", Daren_thinking);
   fasttalk(isColorOn, "drop = paste\n", Daren_thinking);
   fasttalk(isColorOn, "use = grep/cat/...\n", Daren_thinking);
   fasttalk(isColorOn, "inventory = free, copybuffer, top\n", Daren_thinking);
   fasttalk(isColorOn, "=Objects\n", Daren_thinking);
   fasttalk(isColorOn, "room = folder\n", Daren_thinking);
   fasttalk(isColorOn, "item = file\n", Daren_thinking);
   fasttalk(isColorOn, "inventory = ram\n", Daren_thinking);
   fasttalk(isColorOn, "\n", Daren_thinking);
   
   endSegment(isColorOn);

   fasttalk(isColorOn, "Also when editing files can you not exploit the ability to open a shell in vim (idk if you can do that with emacs) to break the game\n", Daren_thinking);
   fasttalk(isColorOn, "And also please don't expoit the ability to open ANY program with the \"editor\" command\n", Daren_thinking);
   

   fasttalk(isColorOn, "\npsst .... hey kid wanna know how to get a shell using the \"editor\" command\n", Daren_thinking);
   fasttalk(isColorOn, "I am assuming youre using bash but you can use dash or zsh as well, or even stuff like python\n", Daren_thinking);
   fasttalk(isColorOn, "first make a new file and write the following:\n\n", Daren_thinking);
   fasttalk(isColorOn, "#!/bin/sh\n", Daren_thinking);
   fasttalk(isColorOn, "bash\n", Daren_thinking);
   fasttalk(isColorOn, "\n", Daren_thinking);
   fasttalk(isColorOn, "Then run this command:\n\n", Daren_thinking);
   fasttalk(isColorOn, "editor bash <the file you just wrote>\n\n", Daren_thinking);
   fasttalk(isColorOn, "this will execte \"bash temp\" and temp is a shell scripts that executes bash\n", Daren_thinking);
   fasttalk(isColorOn, "congrats now you have a shell, go wild and break the game\n", Daren_thinking);
   
   endSegment(isColorOn);

   fasttalk(isColorOn, "eh.. heres how to do it with ruby:\n", Daren_thinking);

   fasttalk(isColorOn, "file:\n\n", Daren_thinking);
   fasttalk(isColorOn, "exec(\"bash\")\n\n", Daren_thinking);
   fasttalk(isColorOn, "command:\n\n", Daren_thinking);
   fasttalk(isColorOn, "editor ruby <the file you just wrote>\n\n", Daren_thinking);
   fasttalk(isColorOn, "\n", Daren_thinking);
   
   fasttalk(isColorOn, "and here is also how to it it with python if you where interested:\n", Daren_thinking);
   fasttalk(isColorOn, "file:\n\n", Daren_thinking);
   fasttalk(isColorOn, "import os\nos.system(\"bash\")\n\n", Daren_thinking);
   fasttalk(isColorOn, "command:\n\n", Daren_thinking);
   fasttalk(isColorOn, "editor python <the file you just wrote>\n\n", Daren_thinking);
   fasttalk(isColorOn, "\n", Daren_thinking);

   endSegment(isColorOn);


   fasttalk(isColorOn, "Last thing I swear!\n", Daren_thinking);
   fasttalk(isColorOn, "Daren: People talk like this\n", Daren_talking);
   fasttalk(isColorOn, "daren: People and think like this\n", Daren_thinking);
   fasttalk(isColorOn, "Your player cannot see people thinking but only them talking\n", Daren_thinking);
   fasttalk(isColorOn, "..anyway the game starts as soon as you press ENTER.\n", Daren_thinking);
   endSegment(isColorOn);


   //bos haha comes from dos but broken haha (its supposed to feel like unix nontheless)
   Computer myComputer= Computer(Text("DAK"), Text("bos"+randomTextNumbers(3)));
   myComputer.on=isColorOn;

   //=some game variables
   //bools
   bool informedAboutCD=false;
   bool hasCD=false;
   bool voidPointer=false;
   bool brokenNetworkManager=true;
   bool hasToSSH=true;
   bool hasWon=false;
   
   //other data types
   IPAdress targetIP=IPAdress();
   Text targetIPName=randomText(8);
   Text ssid="Network"+randomTextNumbers(4);
   Text password=randomText(20);
   Text code=randomTextNumbers(7);


   //=set up folders and files
   //cd
   myComputer.parser.removeCommand("cd");
   myComputer.createFile(File(Path("/a/cd"), randomText(100)), "/root/cd");
   myComputer.deleteFile("/bin/cd");

   //CRippled Archaic SHell RC
   //.crashtc
   myComputer.createFile(File(Path("/a/.crashrc"), Text("")), "/root/.crashrc");
   //note the %U is user %H is host and %D is current directory



   //make the pass and ssid
   myComputer.createFile(File(Path("/a/password-meme.txt"), Text("the password of the network might be "+password+" but I don't know for sure.")), "/home/Desktop/memes/password-meme.txt");
   myComputer.createFile(File(Path("/a/5$|D-7Xt"), Text(ssid)), "/tmp/5$|D-7Xt");



   //clear screen
   execCLEAR(myComputer);
   
   slowtalk(isColorOn, "Boss: Hey you, the new employee... erm.. what was your name...\n", Boss_talking);
   
   fasttalk(isColorOn, "Type in your name\n", Daren_thinking);

   {
      char name[100]; 
      cin.getline(name, 100);
      myComputer.setUser(name);
   }

   slowtalk(isColorOn, "You: "+myComputer.getUser()+" sir.\n", Player_talking);
   slowtalk(isColorOn, "Boss: Ah yes, "+myComputer.getUser()+" right.\n", Boss_talking);
   slowtalk(isColorOn, "Anyway. You're tasked with breaching the TOP network system.\n", Boss_talking);
   slowtalk(isColorOn, "One of our small time hackers managed to find a backdoor in one of their external computers.\n", Boss_talking);
   slowtalk(isColorOn, "I don't know how usable it it but it'll have to make do.\n", Boss_talking);
   slowtalk(isColorOn, "Typing \"help\" should give you some info on how to operate\n", Boss_talking);
   slowtalk(isColorOn, "Good luck!\n", Boss_talking);




   
   do{
      
      //[user@host pwd]#
      fasttalk(myComputer.on, "["+myComputer.getUser()+"@"+myComputer.getHost()+" ");
      if(myComputer.getCurrentFolder().path.len()==0)
         fasttalk(myComputer.on, "/");
      else
         fasttalk(myComputer.on,myComputer.getCurrentFolder().path.wholeT());
      fasttalk(myComputer.on,Text("]# "));
      
      
      myComputer.parser.readLn();
      
      //current command
      Text curCom=myComputer.parser.returnCommandT(0);
      
      
      
      int commandAmount=sizeof(execDef)/sizeof(Text);
      for(int i =0; i<(1+commandAmount); i++){
         if(i==commandAmount){
            unexpectedIO(myComputer.on, "The command inputted is non existant.");
            break;
         }
         
         if(curCom==execDef[i]){
            if(exec[i](myComputer))
               info(myComputer.on, "Action successful.");
            else
               info(myComputer.on, "Action unsuccessful.");
         
            break;
         }
      }

      if(!informedAboutCD){
         informedAboutCD=true;
         fasttalk(isColorOn, "daren: Don't worry I'll help you along the way\n", Daren_thinking);
         fasttalk(isColorOn, "You don't have the cd program in /bin/\n", Daren_thinking);
         fasttalk(isColorOn, "But don't worry the binary is in /root/\n", Daren_thinking);
         fasttalk(isColorOn, "you can do \"copy /root/cd\" to copy it\n", Daren_thinking);
         fasttalk(isColorOn, "then you can do \"copybuffer\" to see where it is (should be at index 0)\n", Daren_thinking);
         fasttalk(isColorOn, "And finally you can do \"paste 0 /bin/\" to paste in the bin folder\n", Daren_thinking);
         fasttalk(isColorOn, "(again pasting the file at index 0)\n", Daren_thinking);
         fasttalk(isColorOn, "And Tada you can use cd now\n", Daren_thinking);
         fasttalk(isColorOn, "Dont forget you can use \"man <command>\" to learn more about a specific command\n", Daren_thinking);
      }else if(!hasCD){

         //did we copy cd?
         File* cd=myComputer.getFile("/bin/cd", true);
         if(cd==nullptr)
            continue;
         
         
         hasCD=true;
         //add the cd command
         char alias[100][100]={"cd", "chgdir", "cngdir", "chngdir"}, description[100]="Changes the current directory.";
         char args[100][100]={"cmd", "txt"}, argsDescription[100]="<directory path>";
         char extraDescription[300]="Examples of command:\ncd /path/starting/from/root\ncd myFolder\ncd path/to/a/folder/in/this/folder";
         myComputer.parser.addCommand(Command(4, alias, description, 2, args, argsDescription, extraDescription));
         
         fasttalk(isColorOn, "daren: Nice, now you can use cd to go through folders\n\n", Daren_thinking);
         fasttalk(isColorOn, "Your goal basically is to ssh into an internal computer.\n", Daren_thinking);
         fasttalk(isColorOn, "But you aren't connected to any networks!\n", Daren_thinking);
         fasttalk(isColorOn, "Make a file /etc/netman/connections/<name>.conf\n", Daren_thinking);
         fasttalk(isColorOn, "in it write exactly this (there is an end line at the end):\n", Daren_thinking);
         fasttalk(isColorOn, "[connection]\n", Daren_thinking);
         fasttalk(isColorOn, "id=<name>\n", Daren_thinking);
         fasttalk(isColorOn, "\n", Daren_thinking);
         fasttalk(isColorOn, "[security]\n", Daren_thinking);
         fasttalk(isColorOn, "pass=<password>\n", Daren_thinking);
         fasttalk(isColorOn, "\n", Daren_thinking);
         fasttalk(isColorOn, "as soon as you write it you'll  be connected\n", Daren_thinking);
         fasttalk(isColorOn, "Use tree in the root folder to get a map of the file tree\n", Daren_thinking);
         fasttalk(isColorOn, "Anyway search for a file containing the password and network name, should be in somewhere on this computer\n", Daren_thinking);
         fasttalk(isColorOn, "(forgot to mention this, I assume you know Unix or GNU/Linux commands)\n", Daren_thinking);

         
      }else if(brokenNetworkManager){
         //void pointer
         if(voidPointer==false && myComputer.getCurrentFolder().path.getDepth()>1 && myComputer.getCurrentFolder().name()=="memes"){
            voidPointer=true;
            slowtalk(isColorOn, "you: void pointer? Wait what?\n", Player_thinking);
         }


         //proper file?
         File* conf=myComputer.getFile("/etc/netman/connections/"+ssid+".conf", true);
         if(conf==nullptr)
            continue;

         Text expected;
         expected+="[connection]\n";
         expected+="id="+ssid+"\n";
         expected+="\n";
         expected+="[security]\n";
         expected+="pass="+password+"\n";

         if(!(expected==conf->cont())){
            fasttalk(isColorOn, "daren: Wrong config, yes I will spam this until you fix it\n", Daren_thinking);
            continue;
         }
         brokenNetworkManager=false;
         //=connecting...
         //con.conf
         myComputer.createFile(File(Path("/a/con.conf"), Text("[Internal Computers]\n"+targetIPName+"\n")), "/etc/con.conf");


         //ip adress
         myComputer.createFolder(Folder(Path("/a/connections")), "/sys/connections");
         {
            //where will the target ip adress be
            int targetAdressFile=rand()%4+1;
            int targetAdressLine=rand()%298;

            vector<IPAdress> allAdresses;
            allAdresses.push_back(targetIP);

            for(int i=1; i<5; i++){
               Text contents;
               for(int j=0; j<298; j++){
                  //in case its the target ip adress add random ip adresses
                  if(targetAdressFile==i && targetAdressLine==j){
                     contents+=targetIPName+": "+targetIP.getIPAdressText()+'\n';
                  }else{
                     //add to all adresses so we don't make duplicates
                     allAdresses.push_back(IPAdress(allAdresses));
                     //get the adress we just added
                     contents+=randomText(8)+": "+(allAdresses.end()-1)->getIPAdressText()+'\n';
                  }
               }
               myComputer.createFile(File(Path("/a/list"+Text(i)+".txt"), contents), "/sys/connections/list1.txt");

            }
         }

         
       
         fasttalk(isColorOn, "daren: Nice, you're connected\n", Daren_thinking);
         fasttalk(isColorOn, "My initial idea was to make you use nmap to find all devices and ssh into them until you found a specific file\n", Daren_thinking);
         fasttalk(isColorOn, "The real action would've been there where you gotta confuse the Admins of the system... anyway\n", Daren_thinking);
         fasttalk(isColorOn, "Since I didn't have enough time to code in networks and nmap, all of the \"connections\" are\n", Daren_thinking);
         fasttalk(isColorOn, "in files on this computer. Your clues are /etc/con.conf and /sys/connections/*\n", Daren_thinking);
         fasttalk(isColorOn, "you might wanna use grep for the second clue\n", Daren_thinking);

         
      }else if(hasToSSH){
         if(myComputer.parser.returnCommandT(0)=="ssh"){
            //correct ip adress?
            if(myComputer.parser.returnCommandT(1)==targetIP.getIPAdressText()){

               
               myComputer.createFile(File(Path("/a/code.code"), "[{0-==;][;[?>?p]p[]=-"+code+"{}[]]][[[[=-+_+_=.,.<>"), "/opt/code.code");

               
               fasttalk(isColorOn, "daren: Nice, you ssh'd\n", Daren_thinking);
               fasttalk(isColorOn, "Pretend I coded in ssh and scp and you copied a file into your computer\n", Daren_thinking);
               fasttalk(isColorOn, "clear it out of all the []\"\"''{}(),.<> with a text editor of your choice and you've won!\n", Daren_thinking);
               hasToSSH=false;
            }
            
         
         }
      }else if(!hasWon){


         //un case the player deletes the file
         File* file=myComputer.getFile("/opt/code.code", true);
         if(file==nullptr)
            continue;

         if(file->cont()==code){
            hasWon=true;
            slowtalk(isColorOn, "Boss: Good job!\n", Boss_talking);
            slowtalk(isColorOn, "Now we will have unlimited access to their network with this code!\n", Boss_talking);
            slowtalk(isColorOn, "Eh, you can go home now we don't need you anymore for today.\n", Boss_talking);
            slowtalk(isColorOn, "boss: I'll get a promotion for sure now!\n", Boss_thinking);
            fasttalk(isColorOn, "daren: Maybe if I had a couple of more months I could finish the game...\n", Daren_thinking);
            fasttalk(isColorOn, "You're free to explore the game, make files, delete folders , etc\n", Daren_thinking);
            fasttalk(isColorOn, "Daren: you won btw\n", Daren_talking);
            slowtalk(isColorOn, "You: Who is this talking... and what did I win?\n", Player_talking);
            slowtalk(isColorOn, "you: Am I starting to hear voices\n", Player_thinking);
            
         }
      
      }


      
   }while(true);
   
   
   system(thisFile.val());
   
   cout << "END\n";
   return 0;
}


void endSegment(bool color){
   char enter[1];
   fasttalk(color, "\n[Press Enter]\n", Daren_talking);
   cin.getline(enter, 99);
}

bool editFile(Text editor, File* virtFile){

   if(virtFile==nullptr)
      return false;


   //=edit file
   //open the file, emptying it in the process
   ofstream realFileW;
   realFileW.open("temp", ios::out | ios::trunc);
   realFileW << virtFile->cont();
   realFileW.close();
   system((editor+" temp").val());   

   //=read file 
   ifstream realFileR ("temp");
   virtFile->cont()="";
   while(realFileR.peek()!=EOF){
      virtFile->cont()+=(char)realFileR.get();
   }
   realFileR.close();
   
   return true;
}


//==commands from user
bool execCD(Computer& inComp){
   if(inComp.goTo(inComp.parser.returnCommandT(1)))
      return true;
   return false;
}
bool execLS(Computer& inComp){
   char spacer='\t';
   
   //long listing format
   bool longList=false;
   
   Text flags=inComp.parser.returnCommandT(1);
   //take in flags only if they are prefixed with a dash
   if(flags[0]=='-'){
      //if any l
      if(flags[1]=='l' || flags[2]=='l')
         longList=true;
      //if 1
      else if(flags[1]=='1')
         spacer='\n';  
   }
   
   //all Folders
   auto allFold=inComp.getCurrentFolder().allFolders();
   for(auto i=allFold.begin(); i!=allFold.end(); i++)
      if(longList){
         fasttalk(inComp.on, intToText((*i)->getDate()), folderColor);
         fasttalk(inComp.on, ' '+(*i)->path.wholeT()+'\n', folderColor);
      }else
         fasttalk(inComp.on, (*i)->name() +spacer, folderColor);
   
   
   
   //all Files
   auto allFile=inComp.getCurrentFolder().allFiles();
   for(auto i=allFile.begin(); i!=allFile.end(); i++)   
      if(longList){
         fasttalk(inComp.on, intToText((*i)->getDate()), fileColor);
         fasttalk(inComp.on, ' '+(*i)->path.wholeT()+'\n', fileColor);
      }else
         fasttalk(inComp.on, (*i)->name() +spacer, fileColor);
   
   fasttalk(inComp.on, Text("\n"), Info);
   
   
   //i cannot see a situation where this action would be unsuccessful
   return true;
   
}
   
bool execCAT(Computer& inComp){
   File* file=inComp.getFile(inComp.parser.returnCommandT(1));
   if(file!=nullptr){
      fasttalk(inComp.on, file->cont()+'\n');
      return true;
   }
   return false;
}

bool execTOUCH(Computer& inComp){
   Text name=inComp.parser.returnCommandT(1);
   if(inComp.createFile(File(Path("/a/"+name)), name))
      return true;
   return false;
}


bool execRM(Computer& inComp){
   
   Text flag=inComp.parser.returnCommandT(1);
   
   
   //are we deleting a folder(-r) or a file(none)
   //for simplicity -r works only on files
   if(flag=="-r"){
      if(inComp.deleteFolder(inComp.parser.returnCommandT(2))){
         info(inComp.on, "Folder removed recursively.");
         return true;
      }
   }else{
      if(inComp.deleteFile(flag)){
         info(inComp.on, "File removed.");
         return true;
      }
   }
   return false;
   
}
bool execMKDIR(Computer& inComp){
   Text name=inComp.parser.returnCommandT(1);
   if(inComp.createFolder(Folder(Path("/a/"+name)), name))
      return true;
   return false;
}

bool execPWD(Computer& inComp){
   
   if(inComp.getCurrentFolder().path.len()==0)
      fasttalk(inComp.on, "/\n");
   else
      fasttalk(inComp.on,inComp.getCurrentFolder().path.wholeT()+'\n');
   
   return true;
}

bool execCLEAR(Computer& inComp){
   for(int i=0; i<1000; i++)
      cout << '\n' << flush;   
   return true;
}

bool execGREP(Computer& inComp){
   //get the file
   File* file=inComp.getFile(inComp.parser.returnCommandT(2));
   if(file==nullptr)
      return false;
   
   //get the search term
   Text pattern=inComp.parser.returnCommandT(1);
   
   int lineNumber=1;
   Text currentLine;
   
   //design copied from ./parser.cpp from readLn   
   for(long unsigned i=0; true; i++){
      currentLine+=file->cont()[i];
      
      if(file->cont()[i]=='\n'){
         //we are the end of the line
         
         //does the line match the patters?
         char* cmpr=strstr(currentLine.val(), pattern.val());
         if(cmpr!=nullptr)
            fasttalk(inComp.on, Text(lineNumber)+": "+currentLine);

         //clear the current line, we are goig to the next line
         currentLine="";
         lineNumber++;
      }
      //are we at the end of the file?
      if(i==file->cont().len()-1){
         
         //does the line match the patters?
         char* cmpr=strstr(currentLine.val(), pattern.val());
         if(cmpr!=nullptr)
            fasttalk(inComp.on, Text(lineNumber)+": "+currentLine);
         
         //end with new line just in case
         fasttalk(inComp.on, '\n');
         break;
         
         
      }
   }      
   
   return true;
}

bool execCOPY(Computer& inComp){
   return inComp.copyToRam(inComp.parser.returnCommandT(1));
}

bool execPASTE(Computer& inComp){   
   return inComp.pasteFromRam(inComp.parser.returnCommandT(1)[0]-'0',inComp.parser.returnCommandT(2));
}

bool execCOPYBUFFER(Computer& inComp){
   if(inComp.parser.returnCommandT(1)=="clear")
      return inComp.clearRam();
   inComp.printItemsInRam();
   return true;
}


bool execVI(Computer& inComp){
   return editFile("vi", inComp.getFile(inComp.parser.returnCommandT(1)));
}
bool execVIM(Computer& inComp){
   return editFile("vim", inComp.getFile(inComp.parser.returnCommandT(1)));
}
bool execNEOVIM(Computer& inComp){
   return editFile("nvim", inComp.getFile(inComp.parser.returnCommandT(1)));
}
bool execHELIX(Computer& inComp){
   return editFile("helix", inComp.getFile(inComp.parser.returnCommandT(1)));
}
bool execEMACS(Computer& inComp){
   //open CLI emacs, not GUI
   return editFile("emacs -nw", inComp.getFile(inComp.parser.returnCommandT(1)));
}
bool execNANO(Computer& inComp){
   return editFile("nano", inComp.getFile(inComp.parser.returnCommandT(1)));
}
bool execMICRO(Computer& inComp){
   return editFile("micro", inComp.getFile(inComp.parser.returnCommandT(1)));
}
bool execEDITOR(Computer& inComp){
   return editFile(inComp.parser.returnCommandT(1), inComp.getFile(inComp.parser.returnCommandT(2)));
}
bool execFREE(Computer& inComp){
   fasttalk(inComp.on, "total: "+Text(inComp.getRamTotal())+"\n");
   fasttalk(inComp.on, "free: "+Text(inComp.getRamFree())+"\n");
   fasttalk(inComp.on, "used: "+Text(inComp.getRamUsage())+"\n");
   return true;
}
bool execTREE(Computer& inComp){
   inComp.getCurrentFolder().printTree(inComp.on);
   
   return true;
}
bool execSSH(Computer& inComp){
   return true;
}

bool execHELP(Computer& inComp){
   auto output=inComp.parser.getAllCommands();

   for(auto i=output.begin(); i!=output.end(); i++){
      fasttalk(inComp.on, "\n============\n", Warning);
      fasttalk(inComp.on, i->aliases[0]+'\n', folderColor);
      fasttalk(inComp.on, i->description);
   }
      fasttalk(inComp.on, "\n============\n\n", Warning);
   
   return true;
}


bool execMAN(Computer& inComp){
   auto allCommands=inComp.parser.getAllCommands();
   Command command;
   Text commandName=inComp.parser.returnCommandT(1);
   //find our command
   for(auto i=allCommands.begin(); i!=allCommands.end(); i++){
      if(commandName==i->aliases[0])
         command=*i;
   }
   //no command?
   if(command.aliasesAmount==0){
      unexpectedIO(inComp.on, "man: The command inputted is non existant.");
      return false;
   }
   //=print command info
   fasttalk(inComp.on, "\n============\n", Warning);
   fasttalk(inComp.on, command.aliases[0]+" ", folderColor);

   //aliases
   fasttalk(inComp.on, '(');
   for(int i=1; i<command.aliasesAmount-1; i++)
      fasttalk(inComp.on, command.aliases[i]+", ");
   fasttalk(inComp.on, command.aliases[command.aliasesAmount-1]+")");

   //args
   fasttalk(inComp.on, "\n============\n", Warning);
   fasttalk(inComp.on, "arguments:\n");
   fasttalk(inComp.on, command.argsDescription);
   fasttalk(inComp.on, "\n============\n", Warning);
   //description
   fasttalk(inComp.on, command.description);
   fasttalk(inComp.on, "\n============\n", Warning);
   fasttalk(inComp.on, command.longDescription);
   fasttalk(inComp.on, "\n============\n", Warning);
   return true;
}