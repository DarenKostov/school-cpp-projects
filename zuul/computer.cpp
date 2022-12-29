/*
  Daren Kostov

  Note:
    do not `delete` files/folders here, the folder class manages that 


*/
#ifndef q
#define q
#include "./text.h"
#include "./globalVarsNFuns.h"
#include "./command.h"
#include "./parser.h"
#include "./path.h"
#include "./file.h"
#include "./memory.h"
#include "./folder.h"
#include "./computer.h"
#endif

#include <vector>
#include <map>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

//could be optimized not to search in a folder that the file/folder is for sure not it

//searches for a file anywhere in a folder, given the Path
File* findFile(Folder* root, Path where){
  
  //every single file in this folder
  auto all=root->allChildFiles();
  
  for(auto i=all.begin(); i!=all.end(); i++){
      if((*i)->path==where){
        return *i;
      }
    }
  return nullptr;
}
//searches for a folder anywhere in a folder, given the Path
Folder* findFolder(Folder* root, Path where){
  
  //every single file in this folder
  auto all=root->allChildFolders();
  
  for(auto i=all.begin(); i!=all.end(); i++){
      if((*i)->path==where){
        return *i;
      }
    }
  return nullptr;
}


Computer::Computer(Text User, Text Host){
  //user and other stuff
  user=User;
  host=Host;
  
  
  // ==parser
  // parser=Parser();
  addAllCommands();
  
  //==file system
  
  //=bin
  Folder* bin=new Folder(Path(Text("/bin")));
  
  //make all commands bins
  auto allCommands=parser.getAllCommands();
  for(auto i=allCommands.begin(); i!=allCommands.end(); i++)
    bin->addFile(new File(Path(Text("/bin/"+i->aliases[0])), randomText(rand()%800+400)));
  
  //=tmp
  Folder* tmp=new Folder(Path(Text("/tmp")));
  
  //fills /tmp with random junk
  //be aware that rand() is called each time and it changes
  for(int i=0; i<rand()%5+5; i++)
    tmp->addFile(new File(Path(Text("/tmp/"+randomText(5))), randomText(rand()%100)));

  for(int i=0; i<rand()%5+5; i++)
    tmp->addFolder(new Folder(Path(Text("/tmp/"+randomText(5)))));
      
  //files in /tmp for testing 
   
  tmp->addFile(new File(Path(Text("/tmp/file001")), Text("this is a file\nthat contains multiple\nlines\nand...\nthat's the file\n:/")));
  

  //=dev
  Folder* dev=new Folder(Path(Text("/dev")));
  
  //null is not a folder normally but acts similarly here, a black hole
  dev->addFolder(new Folder(Path("/dev/null")));

  
  root=new Folder(Path(Text("")));
  root->addFolder(bin);
  root->addFolder(new Folder(Path(Text("/boot"))));
  root->addFolder(dev);
  root->addFolder(new Folder(Path(Text("/etc"))));
  root->addFolder(new Folder(Path(Text("/home"))));
  root->addFolder(new Folder(Path(Text("/lib"))));
  root->addFolder(new Folder(Path(Text("/mnt"))));
  root->addFolder(new Folder(Path(Text("/opt"))));
  root->addFolder(new Folder(Path(Text("/proc"))));
  root->addFolder(new Folder(Path(Text("/root"))));
  root->addFolder(new Folder(Path(Text("/run"))));
  root->addFolder(new Folder(Path(Text("/srv"))));
  root->addFolder(new Folder(Path(Text("/sys"))));
  root->addFolder(tmp);
  root->addFolder(new Folder(Path(Text("/usr"))));
  root->addFolder(new Folder(Path(Text("/var"))));
  root->addFolder(new Folder(Path(Text("/lost+found"))));

  currentFolder=root;

  //==ram
  memory=Memory();

  
  Text txt[10]={"2", "2"};
  
  
  
  
}

void Computer::setRoot(Folder* newRoot){
  delete root;
  root=newRoot;
}




//=navigation

bool Computer::goTo(Text where){
  Folder* nextFolder;
  
  //go to parent
  if(where==".." || where=="../"){ 
    
    //if we are at root or the parent is root
    if(currentFolder->path.getDepth()<=1){
      currentFolder=root;
      return true;
    }
    
    
    //get parent path
    Path parentPath=currentFolder->path.getParent();
    
    //find the parent pointer
    nextFolder=findFolder(root, parentPath.wholeT());
    currentFolder=nextFolder;
    
    return true;
  }else if(where[0]=='/'){
    //if we are give full path
  
      //get path
      Folder* folder=findFolder(root, Path(where));
    
      //is the path given valid? no?
      if(folder==nullptr){
        error(on, Text("Unable to locate folder: \""+where+'"'));
        return false;
      }
      //yes?
      currentFolder=folder;
      return true;
    
    
  
  }else{
    //if the folder is in the current folder
    
    // all folders in current folders
    vector<Folder*> currentChildren=currentFolder->allFolders();
    
    for(auto i=currentChildren.begin(); i!=currentChildren.end(); i++){
      
      //if the folder exists
      if(where==(*i)->name()){
        nextFolder=*i;
        currentFolder=nextFolder;
        return true;
      }
    }
    
    //if the destinations is in the children
    
    //make the path
    Path path=Path(currentFolder->path.wholeT()+'/'+where);
    
    //get path
    Folder* folder=findFolder(currentFolder, path);
  
    //does this path exist in any of the children? no?
    if(folder==nullptr){
      error(on, Text("Unable to locate folder: \""+path.wholeT()+'"'));
      return false;
    }
    //yes?
    currentFolder=folder;
    return true; 

  }
  error(on, Text("Unable to locate folder: \""+where+'"'));
  return false;
}

Folder Computer::getCurrentFolder(){
  return *currentFolder;
}



//=files

bool Computer::deleteFile(Text name){

  //first check if we are giving the name or full path
  if(name[0]=='/'){
    //=delete by full path
    
    Folder* parentFolder=findFolder(root, Path(name).getParent());
    
    //is the path given valid? no?
    if(parentFolder==nullptr){
       unexpectedIO(on, "Parent path non-existant.");
       return false;
    }

    //remove the file from the parent via its name
    if(parentFolder->deleteFile(Path(name).name())){
      return true;
    }
        
  }
  //delete by name in current folder
  
  //if deletion is successfull
  if(currentFolder->deleteFile(name)){
    return true;
  }

  //deletion was not successfull
  unexpectedIO(on, "File path non-existant.");
  return false;
}


bool Computer::createFile(File in, Text name){
  
  //first check if we are giving the name or full path
  if(name[0]=='/'){
    //=create by full path
    
    //get parent path
    Folder* parentFolder=findFolder(root, Path(name).getParent());
    
    //is the path given valid?
    if(parentFolder==nullptr){
       unexpectedIO(on, "Parent path non-existant.");
       return false;
    }

    //create a File (its path will be updated automatically)
    if(parentFolder->addFile(new File(in))){
      return true;
    }
        
  }else{
    //=create by name in current folder
  
    //create a File (its path will be updated automatically)
    if(currentFolder->addFile(new File(in))){
      return true;
    }
  }
  //creation was not successfull
  unexpectedIO(on, "File path already existant.");
  return false;

}

File* Computer::getFile(Text name){
  File* output=nullptr;
  
  //first check if we are giving the name or full path
  if(name[0]=='/'){
    //=get by full path
    
    //get file adress
    output=findFile(root, Path(name));
    
    //is the path given valid?
    if(output==nullptr)
       unexpectedIO(on, "File or parent folder path non-existant.");

    
  }else{
    output=currentFolder->getFile(name);
    
    if(output==nullptr)
       unexpectedIO(on, "File path non-existant.");
  
  }

  return output;
}


//=folders

bool Computer::deleteFolder(Text name){

  //first check if we are giving the name or full path
  if(name[0]=='/'){
    //=delete by full path
    
    Folder* parentFolder=findFolder(root, Path(name).getParent());
    
    //is the path given valid?
    if(parentFolder==nullptr){
       unexpectedIO(on, "Parent path non-existant.");
       return false;
    }

    //remove the file from the parent via its name
    if(parentFolder->deleteFolder(Path(name).name())){
      return true;
    }
        
  }
  //delete by name in current folder
  
  //if deletion is successfull
  if(currentFolder->deleteFolder(name)){
    return true;
  }

  //deletion was not successfull
  unexpectedIO(on, "Folder path non-existant.");
  return false;
}


bool Computer::createFolder(Folder in, Text name){
  
  //first check if we are giving the name or full path
  if(name[0]=='/'){
    //=create by full path
    
    //get parent path
    Folder* parentFolder=findFolder(root, Path(name).getParent());
    
    //is the path given valid?
    if(parentFolder==nullptr){
       unexpectedIO(on, "Parent path non-existant.");
       return false;
    }

    //create a File (its path will be updated automatically)
    if(parentFolder->addFolder(new Folder(in))){
      return true;
    }
        
  }else{
    //=create by name in current folder
  
    //create a File (its path will be updated automatically)
    if(currentFolder->addFolder(new Folder(in))){
      return true;
    }
  }
  //creation was not successfull
  unexpectedIO(on, "Folder path already existant.");
  return false;

}

Folder Computer::getFolder(Text name){
  Folder* output=nullptr;
  
  //first check if we are giving the name or full path
  if(name[0]=='/'){
    //=get by full path
    
    //get file adress
    output=findFolder(root, Path(name));
    
    //is the path given valid?
    if(output==nullptr)
       unexpectedIO(on, "Folder or parent folder path non-existant.");

    
  }else{
    output=currentFolder->getFolder(name);
    
    if(output==nullptr)
       unexpectedIO(on, "File path non-existant.");
  
  }
  
  if(output==nullptr)
    return Folder();
  else
    return *output;
}

Text Computer::getUser(){
  return user;
}
Text Computer::getHost(){
  return host;
}

long Computer::getRamUsage(){
  return memory.getUsage()+100;
}

long Computer::getRamFree(){
  return memory.getFree();
}

long Computer::getRamTotal(){
  return memory.getUsage()+memory.getFree()+100;
}

bool Computer::copyToRam(Text path){
  File* target=getFile(path);

  //wrong input?
  if(target==nullptr)
    return false;

  if(!memory.addFile(*target)){
    warning(on, "Not enough space in the ram, proceeding will cause the system to freeze.");
    return false;
}
  
  return true;
}

bool Computer::pasteFromRam(int id, Text path){

  //things to keep in mind
  //when creating a file the File's name will be the name
  //when creating a file, the path (Text) we provide will be its parent
  //all of the "/a/" are just in case someonbe decides to not input something


  if(!memory.isNotEmpty()){
    error(on, "Memory is empty.");
    return false;
  }

  File target=memory.getFile(id);
    //====gave up on this===== might and most likely will not try to fix/finish this

  
  // //remake the path given if we are provided new file name or not
  // if(path[path.len()-1]=='/'){
  //   //we are not renaming


  //   target=File("/a/"+target.name(), target.cont());

  //   //remove the / at the end of the path
  //   Text tmp=path;
  //   path="";
  //   for(int i=0; i<tmp.len()-1; i++)
  //     path+=tmp[i];

  // }else{
  
  //   //chage the name
  //   target=File("/a/"+Path("/a/"+path).name(), target.cont());

  //   //remove the name from the path
  //   path=Path("/a/"+path).getParent().wholeT();
  // }

  cout << path << '\n' << flush;
  cout << target.path.wholeT() << '\n' << flush;
    
  return createFile(target, path);
}


void Computer::printItemsInRam(){
  fasttalk(on, memory.AllItems());
}


bool Computer::clearRam(){
  if(!memory.isNotEmpty()){
    error(on, "Memory is already empty.");
    return false;
  }
  while(memory.isNotEmpty())
    memory.removeFile(0);

  return false;
}


void Computer::addAllCommands(){

  {
    char alias[100][100]={"cd", "chgdir", "cngdir", "chngdir"}, description[100]="Changes the current directory.";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="<directory path>";
    parser.addCommand(Command(4, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"copy", "c"}, description[100]="Copies a file into the ram.";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="<source path>";
    parser.addCommand(Command(2, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"paste", "p"}, description[100]="pastes all files from ram. OR pastes a specifc file";
    char args[100][100]={"cmd", "txt", "txt"}, argsDescription[100]="<file id> [destination path]";
    char extraDescrption[]="You can ommit the destination path and the file will be p[asted in the current directory\nExamples of the command:\nc 2 /opt/myfolder/\nc 4";
    parser.addCommand(Command(2, alias, description, 3, args, argsDescription));
  }{
    //cp actually stands for just "copy"
    char alias[100][100]={"cp", "copypaste"}, description[100]="copies a file into memory and pastes it.";
    char args[100][100]={"cmd", "txt", "txt"}, argsDescription[100]="<source path> [destination path]";
    parser.addCommand(Command(2, alias, description, 3, args, argsDescription));
  }{
    char alias[100][100]={"rm", "remove"}, description[100]="Deletes a file or a folder";
    char args[100][100]={"cmd", "txt", "txt"}, argsDescription[100]="[flags] <file path>";
    parser.addCommand(Command(2, alias, description, 3, args, argsDescription));
  }{
    char alias[100][100]={"man", "manual"}, description[100]="Shows detals on how to use a program.";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="<program>";
    parser.addCommand(Command(2, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"free", "fr"}, description[100]="Shows the ram usage.";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="<flag>";
    parser.addCommand(Command(2, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"mv", "move"}, description[100]="Moves a file.";
    char args[100][100]={"cmd", "txt", "txt"}, argsDescription[100]="<source path> <destination path>";
    parser.addCommand(Command(2, alias, description, 3, args, argsDescription));
  }{
  //Table Of Processes, i know it doesn't stand for that, but makes more sense as an alieas than "top CPU consumers"
    char alias[100][100]={"top", "tbloprc", "tbloprs"}, description[100]="Shows process's name, memory usage, and cpu usage";
    char args[100][100]={"cmd"}, argsDescription[100]="none";
    parser.addCommand(Command(3, alias, description, 1, args, argsDescription));
  }{
  //doesnt copy to the buffer, its the buffer thats copied into
    char alias[100][100]={"copybuffer", "cb", "copybank"}, description[100]="Shows you what files you have in the copy buffer.";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="[clear]";
    parser.addCommand(Command(3, alias, description, 2, args, argsDescription));
  }
  {
    char alias[100][100]={"ssh", "secureshell"}, description[100]="Secure Shell";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="<who>@<adress>\n<adress>";
    parser.addCommand(Command(2, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"scp", "securecopy"}, description[100]="Secure, Contain, Protect!\n\nAhem, SSH secure file copy";
    char args[100][100]={"cmd", "txt", "txt"}, argsDescription[100]="<who>@<adress>:<source path> <who>@<adress>:<destination path>";
    parser.addCommand(Command(2, alias, description, 3, args, argsDescription));
  }{
    char alias[100][100]={"cat", "catout"}, description[100]="Concatenate files and print on the standard output. tl;dr Print files into terminal.";
    char args[100][100]={"cmd", "txt", "txt"}, argsDescription[100]="<file path>";
    parser.addCommand(Command(2, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"grep"}, description[100]="Print lines from a file that match a pattern.";
    char args[100][100]={"cmd", "''", "txt"}, argsDescription[100]="<pattern> <file path>";
    parser.addCommand(Command(2, alias, description, 3, args, argsDescription));
  }{
    char alias[100][100]={"tree"}, description[100]="Print a tree of all child folders/files";
    char args[100][100]={"cmd"}, argsDescription[100]="none";
    parser.addCommand(Command(1, alias, description, 1, args, argsDescription));
  }{
    char alias[100][100]={"exit", "quit"}, description[100]="Exits the game";
    char args[100][100]={"cmd"}, argsDescription[100]="none";
    parser.addCommand(Command(2, alias, description, 1, args, argsDescription));
  }{
    char alias[100][100]={"ls", "list"}, description[100]="Lists the items in the current directory";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="flags";
    parser.addCommand(Command(2, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"touch", "tch"}, description[100]="Make an empty file";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="<file path>";
    parser.addCommand(Command(2, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"mkdir", "makedirectory", "mkfold"}, description[100]="Make an empty folder";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="<folder path>";
    parser.addCommand(Command(3, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"pwd"}, description[100]="Print working directory";
    char args[100][100]={"cmd"}, argsDescription[100]="none";
    parser.addCommand(Command(1, alias, description, 1, args, argsDescription));
  }{
    char alias[100][100]={"clear", "cl"}, description[100]="Clears the screen, unlike other commands this is instant.";
    char args[100][100]={"cmd"}, argsDescription[100]="none";
    parser.addCommand(Command(2, alias, description, 1, args, argsDescription));
  }{
    char alias[100][100]={"vi"}, description[100]="Visual Instrument- text editor";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="<file path>";
    char extraDescrption[]="The default editor for Unix-based systems\nExamples of the command:\nvi myfile.txt";
    parser.addCommand(Command(1, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"vim"}, description[100]="Vi IMproved- text editor";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="<file path>";
    char extraDescrption[]="Vi but with more features\nExamples of the command:\nvim myfile.txt";
    parser.addCommand(Command(1, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"neovim", "nvim"}, description[100]="The modern Vim- text editor";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="<file path>";
    char extraDescrption[]="Vim but faster, smaller, more versitile and with a better config/plugin system.\n(Vim is still a very good option for writing code)\nExamples of the command:\nneovim myfile.txt";
    // parser.addCommand(Command(2, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"helix", "hx"}, description[100]="Post modern Vim- text editor";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="<file path>";
    char extraDescrption[]="\"If Neovim is the modern Vim, then Helix is post-modern.\"\nIn may words this is an IDE but in the terminal.\n(I also wrote this project with it)\nExamples of the command:\nhelix myfile.txt";
    parser.addCommand(Command(2, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"emacs"}, description[100]="Editor MACroS- text editor";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="<file path>";
    char extraDescrption[]="A text editor with a lot of macros.\n(This is also the editor most students use at school)\nExamples of the command:\nemacs myfile.txt";
    parser.addCommand(Command(1, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"nano"}, description[100]="Nano’s ANOther editor- text editor";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="<file path>";
    char extraDescrption[]="A friendly editor, for people who just want to edit a file, without the harsh learning curve.\nExamples of the command:\nnano myfile.txt";
    parser.addCommand(Command(1, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"micro"}, description[100]="Terminal-based text editor- text editor";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="<file path>";
    char extraDescrption[]="I don't actually know a lot about this editor except that people say its good.\nExamples of the command:\nmacro myfile.txt";
    parser.addCommand(Command(1, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"editor", "e"}, description[100]="text editor";
    char args[100][100]={"cmd", "txt", "txt"}, argsDescription[100]="<editor> <file path>";
    char extraDescrption[]="For when you use an editor I havent made a specific command for\n(or when you wanna exploit this feature and run whatever you want)\nExamples of the command:\neditor eclipse myfile.txt #hahaha CLI is no more\neditor rm myfile.txt #hahaha broke this game";
    parser.addCommand(Command(1, alias, description, 3, args, argsDescription));
  }{
    char alias[100][100]={"cat << EOF > myfile", "cat > myfile << EOF"}, description[100]="a text editor?";
    char args[100][100]={"cmd", "txt", "txt", "txt", "txt"}, argsDescription[100]="EOF is with what you end the file, myfile is the filepath";
    char extraDescrption[]="Thats how a Unix Haxer edits files\nExamples of the command:\n cat << :wq > myfile.txt\ncat > myfile << :x";
    parser.addCommand(Command(2, alias, description, 5, args, argsDescription));
  }
  
}

