#include <jni.h>
#include <stddef.h>
#include "example_Example.h"
#include "xrep.h"

/* Cast char** array, not <string> to jArray etc*/
JNIEXPORT jint JNICALL Java_example_Example_change_1table(JNIEnv *env, jobject obj, jobjectArray old, jobjectArray curr, jint len) {
	int j,i;
	jclass intClass  = (*env)->FindClass(env,"[[I");
	jsize width = (*env)->GetArrayLength(env,old);
	jobjectArray jold = (*env)->NewObjectArray(env,width,charClass,NULL);
	for (i=0;i<width;i++) {
		jcharArray *line = (*env)->GetObjectArrayElement(env, arr, i);
		int height = (*env)->GetArrayLength(env, line);
		jcharArray jline = (*env)->NewIntArray(env, height);
		jint *pos = (*env)->GetCharArrayElements(env, line, 0);
		jint jpos[height];
		for (j=0;j<height; j++) {
			;
		}

		(*env)->SetCharArrayRegion(env,jline,0,height);
		(*env)->ReleaseCharArrayElements(env, line, pos,0);
		(*env)->ReleaseCharArrayElements(env, jline, jpos,0);
		
		(*env)->SetObjectarrayElement(env,jObjarray,i,jline);
		(*env)->DeleteLocalRef(env,jline);

	}
	return 0;
}
