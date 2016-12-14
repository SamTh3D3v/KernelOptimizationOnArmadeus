#include <linux/pagemap.h>
#include <linux/file.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h> 
#include <linux/dcache.h> 
#include <linux/module.h>

#include <linux/init.h>
#include <linux/proc_fs.h>
#include "../../include/linux/seq_file.h"

#include "ElementsSructs.h"
#include "FileLinkedListOperations.h"
#include "PageLinkedListOperations.h"
#include "TransitionLinkedListOperations.h"
#include "TransitionTableOperations.h"



static int lynx_monitor_proc_open(struct inode *inode, struct  file *file);
static ssize_t lynx_monitor_proc_write(struct file* file, const char* buf, size_t len, loff_t* offset);
int filemap_fault_handler(struct vm_area_struct *vma, struct vm_fault *vmf);
static void *lynx_events_seq_start(struct seq_file *s, loff_t *pos);
static void *lynx_events_seq_next(struct seq_file *m, void *v, loff_t *pos);
static void lynx_events_seq_stop(struct seq_file *m, void *v);
static int lynx_events_seq_show(struct seq_file *m, void *v);
static int __init lynx_init (void);
static void __exit Lynx_exit (void);


static const struct file_operations lynx_monitor_proc_fops =
{
	.owner   = THIS_MODULE,
	.open    = lynx_monitor_proc_open,
	.read    = seq_read,
	.write   = lynx_monitor_proc_write,
	.llseek  = seq_lseek,
	.release = single_release,
};

static struct seq_operations lynx_events_seq_ops =
{
	.start = lynx_events_seq_start, /* La fonction start permet d ’ initialiser la lecture */
	.next  = lynx_events_seq_next,/* Verifier s’il reste encore des données à lire et donne l’adresse de l’élément suivant à lire */
	.stop  = lynx_events_seq_stop, /* Vérifie la condition darrêt de la boucle de lecture */
	.show  = lynx_events_seq_show,  /* Fonction d’affichage du contenu*/
};
static struct jprobe jprobe_filemap_fault = {
.entry = filemap_fault_handler ,
.kp = {
.symbol_name = "filemap_fault" ,
},
};

  FileNode *filesListHead = NULL;  
  FileNode *currentFileNode = NULL;
  PageNode *currentPageNode = NULL;
  int sourcePage = -1;
  int destinationPage = -1;
  
  
  
  //proc related
  #define PROC_FILE "lynx"
  #define BUF_SIZE 4096
  /* buffer des évènements sur fichier*/
int events [BUF_SIZE];
/* indice de lecture */
static int event_rpos = 0;
/* indice d ’é criture */
static int event_wpos = 0;
FileNode *procFilesListHead = NULL; //used to print the list to proc

/* Arret de l'excution des handlers des jprobe*/
static unsigned int stop=0;


static int lynx_monitor_proc_open(struct inode *inode, struct  file *file)
{
	printk(KERN_INFO "PROC : OPEN PROC\n");
	return single_open(file, lynx_events_seq_show,NULL);
	//use this one is you want to print the files sequentially 
	//return seq_open(file, &lynx_events_seq_ops);  
}
static ssize_t lynx_monitor_proc_write(struct file* file, const char* buf, size_t len, loff_t* offset)
{
        return len ;
}

int filemap_fault_handler(struct vm_area_struct *vma, struct vm_fault *vmf)
{
  struct file *file = vma->vm_file;
  //printk(KERN_INFO "Lynx: filemap_fault is executed\n") ;
  //printk(KERN_INFO "LYNXN: requested fils %s \n",file->f_dentry->d_name.name);
  //printk(KERN_INFO "LYNXN: requested paGe %lu \n",vmf->pgoff);
  currentFileNode = insertFileNode(&filesListHead , file->f_dentry->d_name.name);
  destinationPage = vmf->pgoff; //to do : change int to ul
  insertInTransitionTable(currentFileNode , sourcePage, destinationPage);
  sourcePage = destinationPage;
  EXPORT_SYMBOL(filesListHead);
  jprobe_return () ;
  return 0;
}

static void *lynx_events_seq_start(struct seq_file *s, loff_t *pos)
{
       // printk(KERN_INFO "LYNX: Lynx events seq_start is executed \n");     
	procFilesListHead = filesListHead;
	return procFilesListHead;
}

static void *lynx_events_seq_next(struct seq_file *m, void *v, loff_t *pos)
{
        printk(KERN_INFO "LYNX: Lynx events seq next is executed \n");
	if(procFilesListHead == NULL)
          printk(KERN_INFO "LYNX: procFilesListHead is NULL \n");
	/*if(procFilesListHead->next !=NULL){
	  procFilesListHead =procFilesListHead->next;
	  return procFilesListHead;
	}*/	
	return procFilesListHead;
}

static void lynx_events_seq_stop(struct seq_file *m, void *v)
{
        //printk(KERN_INFO "LYNX: Lynx events seq_stop is executed \n");
   	seq_printf(m,"\n---------------------------------------------------\n");
}

static int lynx_events_seq_show(struct seq_file *m, void *v)
{	
        //use The v pointer to Print a Page list or a transition list 
	PrintListFileTransitions_seq(filesListHead, m);	
	return 0;
}

static int __init lynx_init (void)
{
 int res ;
 res = register_jprobe(&jprobe_filemap_fault ) ; 
 if (res <0)
 {
   printk (KERN_INFO "LYNX : Erreur pose jprobe ...\ n " ) ;
 return -1;
 }
 //proc entry point 
if (proc_create(PROC_FILE,S_IWUGO|S_IRUGO,NULL,&lynx_monitor_proc_fops)== NULL){
   printk (KERN_INFO " ERROR - proc_create () failed \ n " ) ;
   return -1;
}
 printk ( KERN_INFO "LYNX : Module LYNX charge \ n " ) ;
 return 0;
}

static void __exit Lynx_exit (void)
{
  remove_proc_entry(PROC_FILE ,NULL);
 unregister_jprobe(&jprobe_filemap_fault) ;
 printk(KERN_INFO "LYNX : Module LYNX decharge \ n " ) ;
}



module_init(lynx_init);
module_exit(Lynx_exit);

MODULE_LICENSE("GPL");

