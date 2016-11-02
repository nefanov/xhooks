#include <stddef.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <X11/Xlib.h>
#include "Xreplacer.h"

using namespace std;
/* Unitary JNI-based construction */

/* this function replaces an old symbol in the X keyboard map with the new one */
int change_sym(char* old,char* curr);

/* EP for table replace*/
int change_table(string* old, string* curr, size_t len) {
    for (int i=0;i<len;i++) {
        char *old_cast = strdup(old[i].c_str());
        char *curr_cast = strdup(curr[i].c_str());
        if (change_sym(old_cast, curr_cast)) {
            free(old_cast);
            free(curr_cast);
            return 1;
        }
    }
	return 0;
}

/* change_sym implementation */
int change_sym(string old,string curr) {
	Display *display;
	if (!(display = XOpenDisplay("")) ) {
		fprintf(stderr, "Can't open display %s\n", XDisplayName(""));
		return 1;
	}

	int	nrepKeycode;
	KeySym oldsym = XStringToKeysym (old.c_str());
	KeySym symbol = XStringToKeysym (curr.c_str());
	nrepKeycode = XKeysymToKeycode (display, oldsym);
	XChangeKeyboardMapping (display, nrepKeycode, 1, &symbol, 1);

	XFlush(display);
	XCloseDisplay(display);
	return 0;
}

/* Cast  jobjectArray to string* etc*/
JNIEXPORT jint JNICALL Java_Xreplacer_change_1table(JNIEnv *env, jobject obj, jobjectArray old, jobjectArray curr)
{
	// retrieve the java.util.List interface class
	jclass cList = env->FindClass("java/util/List");

// retrieve the toArray method and invoke it
	jmethodID mToArray = env->GetMethodID(cList, "toArray", "()[Ljava/lang/Object;");
	if(mToArray == NULL)
		return -1;
	jobjectArray array = (jobjectArray)env->CallObjectMethod(old, mToArray);

// now create the string arrays
	std::string* sArray_old = new std::string[env->GetArrayLength(array)];
	for(int i=0;i<env->GetArrayLength(array);i++) {
		// retrieve the chars of the entry strings and assign them to the array!
		jstring strObj = (jstring)env->GetObjectArrayElement(array, i);
		const char * chr = env->GetStringUTFChars(strObj, NULL);
		sArray_old[i].append(chr);
		env->ReleaseStringUTFChars(strObj, chr);

	}

	array = (jobjectArray)env->CallObjectMethod(curr, mToArray);

	std::string* sArray_curr = new std::string[env->GetArrayLength(array)];
	for(int i=0;i<env->GetArrayLength(array);i++) {
		// retrieve the chars of the entry strings and assign them to the array!
		jstring strObj = (jstring)env->GetObjectArrayElement(array, i);
		const char * chr = env->GetStringUTFChars(strObj, NULL);
		sArray_curr[i].append(chr);
		env->ReleaseStringUTFChars(strObj, chr);

	}


	return change_table(sArray_old,sArray_curr,env->GetArrayLength(array) );
}
