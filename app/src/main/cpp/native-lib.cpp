#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGD(...)	__android_log_print(ANDROID_LOG_DEBUG, "TEST", __VA_ARGS__)

static void logArray(const int* arr, int len)
{
    char item[100];
    for (int i = 0; i < len; i++) {
        snprintf(item, sizeof(item), "%x", arr[i]);
        LOGD("arr[%d] = %s", i, item);
    }
}

void CallJavaWorker(JNIEnv* env, jobject worker, int *output)
{
    jclass cls = env->GetObjectClass(worker);
    jmethodID mid = env->GetMethodID(cls, "work", "()V");
    if (mid == nullptr) {
        return;
    }

    env->CallVoidMethod(worker, mid);
    output[0] = 0x11111111;
}

extern "C"
JNIEXPORT void JNICALL
Java_jp_co_normee_bugjni_MainActivity_nativeTest(JNIEnv *env, jobject thiz, jobject worker)
{
    int arr[1] = {};

    for(int step=0; step<2; step++) {
        if (step == 0) {
            CallJavaWorker(env, worker, arr);
            int res = arr[0];

            int array[] = {res, 0x22222222, 0x33333333, res};
            int len = sizeof(array) / sizeof(int);

            logArray(array, len);
            LOGD("array[2] = %d", array[2]);
        }
    }
}
