#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGD(...)	__android_log_print(ANDROID_LOG_DEBUG, "TEST", __VA_ARGS__)

static void logArray(const int* arr, int len)
{
    char item[100];

    for (int i = 0; i < len; i++) {
        int v = arr[i];
        snprintf(item, 100,"%d", v);
        LOGD("arr[%d] = %s", i, item);
    }
}

void CallJavaWorker(JNIEnv* env, jobject worker, float *output)
{
    jclass cls = env->GetObjectClass(worker);
    jmethodID mid = env->GetMethodID(cls, "work", "()V");
    if (mid == nullptr) {
        return;
    }

    env->CallVoidMethod(worker, mid);
    output[0] = 999;
}

extern "C"
JNIEXPORT jint JNICALL
Java_jp_co_normee_bugjni_MainActivity_nativeTest(JNIEnv *env, jobject thiz, jobject worker)
{
    int ret;
    for(int step=0; step<2; step++) {
        if (step == 0) {
            float output[2] = {};
            CallJavaWorker(env, worker, output);
            int sum = (int)(output[0]);
            ret = (int)(output[1]);

            const int LEN = 5;
            int array[LEN] = {8888, 9999, 1, sum, ret};

            logArray(array, LEN);
        }
    }
    return ret;
}
