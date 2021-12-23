#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGD(...)	__android_log_print(ANDROID_LOG_DEBUG, "TEST", __VA_ARGS__)

static void logArray(const int* arr, int len)
{
    static char item[100];
    for (int i = 0; i < len; i++) {
        snprintf(item, sizeof(item), "%d", arr[i]);
        LOGD("item[%d] = %d", i, arr[i]);
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
    output[0] = 2;
}

extern "C"
JNIEXPORT void JNICALL
Java_jp_co_normee_bugjni_MainActivity_nativeTest(JNIEnv *env, jobject thiz, jobject worker)
{
    int arr[1] = {1};

    for(int step=0; step<arr[0]; step++) {
        if (step == 0) {
            CallJavaWorker(env, worker, arr);
            int res = arr[0];

            static int array[] = {res, 2, 3, 4};
            int len = sizeof(array) / sizeof(int);

            // array[1, 2] will be [0, 0] on:
            //   Nexus 5X: 7.1.2, 8.1.0
            //   Huawei CPN_W09: 7.0
            logArray(array, len);
            LOGD("array[1] = %x", array[1]);
        }
    }
}
