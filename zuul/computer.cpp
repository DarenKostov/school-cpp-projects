/*
  Daren Kostov
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


Computer::Computer(){
  
  //==parser
  addAllCommands();
  
  //==file system
  
  //=bin
  Folder* bin=new Folder(Path(Text("/bin")));
  
  
  //make all commands bins
  auto allCommands=parser.getAllCommands();
  for(auto i=allCommands.begin(); i!=allCommands.end(); i++)
    bin->addFile(new File(Path(Text("/bin/"+i->aliases[0])), randomText(100)));
  
      
  root=new Folder(Path(Text("")));
  root->addFolder(bin);
  root->addFolder(new Folder(Path(Text("/boot"))));
  root->addFolder(new Folder(Path(Text("/dev"))));
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
  root->addFolder(new Folder(Path(Text("/tmp"))));
  root->addFolder(new Folder(Path(Text("/usr"))));
  root->addFolder(new Folder(Path(Text("/var"))));
  root->addFolder(new Folder(Path(Text("/lost+found"))));

  currentFolder=root;

  //==ram
  memory=Memory();

  
  Text txt[10]={"2", "2"};
  
  
  
  
}

void Computer::setRoot(Folder* newRoot){
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
    
    //find the parent
    nextFolder=findFolder(root, parentPath.wholeT());
    currentFolder=nextFolder;
    
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
  }
  error(on, Text("Unable to locate folder: \""+where+'"'));
  return false;
}

Folder Computer::getCurrentFolder(){
  return *currentFolder;
}



//=files

bool Computer::deleteFile(Text name){
  Path path;
  //first check if we are giving the name or full path
  if(name[0]=='/'){
    // //delete by full path
    //==Currently you can delete files only by name if you are in their parent directory
  }
  
  //delete by name
    
  //get path
  // "/path/to/folder" + "/" + "name of file" 
  path=currentFolder->path.wholeT()+'/'+name;
  
  //if deletion is successfull
  if(currentFolder->deleteFile(name)){
    // allFiles.erase(path.wholeT());
    return true;
  }
  //deletion was not successfull
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
    char args[100][100]={"cmd", "txt", "txt"}, argsDescription[100]="<destination path> [file id]";
    parser.addCommand(Command(2, alias, description, 2, args, argsDescription));
  }{
    char alias[100][100]={"cp", "copypaste"}, description[100]="copies a file into memory and pastes it.";
    char args[100][100]={"cmd", "txt", "txt"}, argsDescription[100]="<source path> <destination path>";
    parser.addCommand(Command(2, alias, description, 3, args, argsDescription));
  }{
    char alias[100][100]={"rm", "remove"}, description[100]="Deletes a file.";
    char args[100][100]={"cmd", "txt"}, argsDescription[100]="<file path>";
    parser.addCommand(Command(2, alias, description, 2, args, argsDescription));
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
    char alias[100][100]={"cb", "copybuffer", "copybank"}, description[100]="Shows you what files you have in the copy buffer.";
    char args[100][100]={"cmd"}, argsDescription[100]="none";
    parser.addCommand(Command(3, alias, description, 1, args, argsDescription));
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
    char args[100][100]={"cmd", "txt", "txt"}, argsDescription[100]="<pattern> <file path>";
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
  }
  
}

