//#define CURL_STATICLIB
//#pragma comment (lib, "wldap32.lib")
//#pragma comment (lib, "ws2_32.lib")
//#pragma comment(lib, "CRYPT32.lib")
//#pragma comment(lib, "Normaliz.lib")

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct MemoryStruct {
    char* memory;
    size_t size;
};

static size_t
WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;

    char* ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int main(void)
{
    CURL* curl_put;
    CURL* curl_post;
    CURLcode res;
    int quit = 0;
    int init = 0;
    //int gnum = 0;

    struct MemoryStruct chunk;

    chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
    chunk.size = 0;    /* no data at this point */

    struct curl_slist* headerlist = NULL;
    headerlist = curl_slist_append(headerlist, "Content-Type: application/json");

    //char name[100] = "test1";
    //char date[100] = "2023";
    char acceleration[10] = "0.1";
    char gaussMagnetic[10] = "0.1";
    char angularRate[10] = "0.1";
    char underwaterMicrophone[10] = "0.1";
    char gesture[10] = "0.1";
    char proximity[10] = "0.1";
    char dryAmbientLight[10] = "0.1";
    char dryAmbientRGB[10] = "0.1";
    char dryBarometricPressure[10] = "0.1";
    char dryTemperature[10] = "0.1";
    char dryHumidity[10] = "0.1";
    char underwaterPressure[10] = "0.1";
    char underwaterTemperature[10] = "0.1";
    char underwaterDepth[10] = "0.1";
    char seaLevelAltitude[10] = "0.1";
    char underwaterPictureLow[10] = "0.1";
    char underwaterPictureHigh[10] = "0.1";
    char underwaterVideoWithoutMic[10] = "0.1";
    char underwaterVideoWithMic[10] = "0.1";
    char gnss[30] = "37.8847493, 127.1720248";
    char title[1000] = "title_test";
    char note[1000] = "���ӵ�: 0.1, ���ӵ�: 0.1, ���ڱ�: 0.1, ����: 0.1, �ڼ�: 0.1, ������: 0.1, �ֺ���: 0.1, �ֺ���: 0.1, ���: 0.1, �µ�: 0.1, ����: 0.1, ����: 0.1, ����: 0.1, ��: 0.1, ����: 0.1, ���� ����(���ػ�): 0.1, ���� ����(���ػ�): 0.1, ���� ����(���� ������): 0.1, ���� ����(���� ����): 0.1, ��ġ: 0.1";
    char appendix[1000] = "appendix_test";
    char vlc[100] = "BLUE";
    char latitude[100] = "37.8847493";
    char longitude[100] = "127.1720248";

    //char postthis[1000] = "{\"name\": \"test1\", \"date\": \"2023\", \"acceleration\": \"0.1\", \"gaussMagnetic\": \"0.1\", \"angularRate\": \"0.1\", \"underwaterMicrophone\": \"0.1\", \"gesture\": \"0.1\", \"proximity\": \"0.1\", \"dryAmbientLight\": \"0.1\", \"dryAmbientRGB\": \"0.1\", \"dryBarometricPressure\": \"0.1\", \"dryTemperature\": \"0.1\", \"dryHumidity\": \"0.1\", \"underwaterPressure\": \"0.1\", \"underwaterTemperature\": \"0.1\", \"underwaterDepth\": \"0.1\", \"seaLevelAltitude\": \"0.1\", \"underwaterPictureLow\": \"0.1\", \"underwaterPictureHigh\": \"0.1\", \"underwaterVideoWithoutMic\": \"0.1\", \"underwaterVideoWithMic\": \"0.1\", \"gnss\": \"0.1\"}";
    //char postthis[1000] = "{\"authKey\": \"0\", \"type\": \"0\", \"title\": \"testtitle\", \"note\": \"notetest\", \"appendix\": \"appendixtest\", \"vlc\": \"vlctest\", \"latitude\": \"10\", \"longitude\": \"20\", \"accountType\": \"0\"}";
    //char postthis[1000] = "{\"authKey\": \"0\", \"type\": \"0\", \"title\": \"testtitle\", \"note\": \"notetest\", \"appendix\": \"appendixtest\", \"vlc\": \"vlctest\", \"latitude\": \"10\", \"longitude\": \"20\", \"accountType\": \"0\"}";
    //char login[1000]= "{\"userId\": \"mhnet\", \"password\": \"111111\"}";
    char input[100];
    char inputID[100];
    char inputPW[100];
    char* temp;
    char chunk_temp[1000];
    char LOGIN_URL[1000] = "http://www.uhsdm.site/v1/users/login?userId=mhnet&password=111111";
    //char* ID_CODE;
    char POST_URL[2000] = "http://www.uhsdm.site/v1/posts?authKey=0&type=0&title=test2023title&note=test2023note&appendix=test2023appendix&vlc=test2023vlc&latitude=37.8847493&longitude=127.1720248&accountType=1";

    curl_put = curl_easy_init();
    curl_post = curl_easy_init();
    if (!curl_put && !curl_post) {
        quit = 1;
    }
    while (!quit) {

        if (!init) {
            curl_easy_setopt(curl_put, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl_put, CURLOPT_HTTPHEADER, headerlist);
            //curl_easy_setopt(curl_put, CURLOPT_POSTFIELDS, login);
            curl_easy_setopt(curl_put, CURLOPT_CUSTOMREQUEST, "PUT");
            /* send all data to this function  */
            curl_easy_setopt(curl_put, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
            /* we pass our 'chunk' struct to the callback function */
            curl_easy_setopt(curl_put, CURLOPT_WRITEDATA, (void*)&chunk);
            curl_easy_setopt(curl_put, CURLOPT_URL, LOGIN_URL);
#ifdef _WIN32
            curl_easy_setopt(curl_put, CURLOPT_COOKIEJAR, "D:\\data\\cookies.txt");
#else
            curl_easy_setopt(curl_put, CURLOPT_COOKIEJAR, "/home/kmuscrc/PROJECT/DIVERSNS/COOKIES/cookies.txt");
#endif
            //curl_easy_setopt(curl_put, CURLOPT_COOKIELIST, "FLUSH");

            curl_easy_setopt(curl_post, CURLOPT_HTTPHEADER, headerlist);
            //curl_easy_setopt(curl_post, CURLOPT_POSTFIELDS, postthis);
            curl_easy_setopt(curl_post, CURLOPT_POSTFIELDS, "{}");
            curl_easy_setopt(curl_post, CURLOPT_POST, 1L);
            //curl_easy_setopt(curl_post, CURLOPT_CUSTOMREQUEST, "POST");
            /* send all data to this function  */
            curl_easy_setopt(curl_post, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
            /* we pass our 'chunk' struct to the callback function */
            curl_easy_setopt(curl_post, CURLOPT_WRITEDATA, (void*)&chunk);

            sprintf(note, "Accelerometer Data: %s, Gyroscope Data: %s, Magetometer Data: %s, Underwater Microphone: %s, Gesture: %s, Proximity: %s, Dry Ambient Light: %s, Dry Ambient RGB: %s, Dry Barometic Pressure: %s, Dry Temperature: %s, Dry Humidity: %s, Underwater Pressure: %s, Underwater Depth: %s, Altitude: %s, Underwater Temperature: %s, Underwater Picture(Still Shot) - Low Resolution: %s, Underwater Picture(Still Shot) - High Resolution: %s, Underwater Video Without Microphone: %s, Underwater Video With Microphone: %s, GNSS: %s", acceleration, angularRate, gaussMagnetic, underwaterMicrophone, gesture, proximity, dryAmbientLight, dryAmbientRGB, dryBarometricPressure, dryTemperature, dryHumidity, underwaterPressure, underwaterDepth, seaLevelAltitude, underwaterTemperature, underwaterPictureLow, underwaterPictureHigh, underwaterVideoWithoutMic, underwaterVideoWithMic, gnss);
            sprintf(POST_URL, "http://www.uhsdm.site/v1/posts?authKey=0&type=0&title=%s&note=%s&appendix=%s&vlc=%s&latitude=%s&longitude=%s&accountType=1", title, curl_easy_escape(curl_put, note, strlen(note)), appendix, vlc, latitude, longitude);
            curl_easy_setopt(curl_post, CURLOPT_URL, POST_URL);

            init = 1;
        }

        while (!quit) {//�α���
            printf("�����ϼ���.\n1.�α���\n2.����\n");
            scanf("%s", input);
            if (strcmp(input, "1") == 0) {
                printf("���̵� �Է����ּ���.\n");
                scanf("%s", inputID);
                printf("��й�ȣ�� �Է����ּ���.\n");
                scanf("%s", inputPW);
                //sprintf(login, "{\"userId\": \"%s\", \"password\": \"%s\"}", inputID, inputPW);
                //curl_easy_setopt(curl_put, CURLOPT_POSTFIELDS, login);
                sprintf(LOGIN_URL, "http://www.uhsdm.site/v1/users/login?userId=%s&password=%s", inputID, inputPW);
                curl_easy_setopt(curl_put, CURLOPT_URL, LOGIN_URL);

                /* Perform the request, res will get the return code */
                res = curl_easy_perform(curl_put);
                /* Check for errors */
                if (res != CURLE_OK)
                    fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));

                //printf("ûũ : %s\n", chunk.memory);
                sprintf(chunk_temp, "%s", chunk.memory);
                temp = strtok(chunk_temp, " {}\":,");
                temp = strtok(NULL, " {}\":,");
                temp = strtok(NULL, " {}\":,");
                //printf("ûũ : %s\nûũ���� : %s\n���� : %s\n", chunk.memory, chunk_temp, temp);
                free(chunk.memory);
                chunk.memory = malloc(1);
                chunk.size = 0;
                if (strcmp(temp, "true") == 0) {
                    printf("�α��� ����\n");
                    //ID_CODE = strtok(NULL, " {}\":,");
                    //sprintf(POST_URL, "http://52.78.83.63:8080/api/underwater/%s", ID_CODE);
                    //printf("���˿�:%s\n",POST_URL);
                    //curl_easy_setopt(curl_post, CURLOPT_URL, POST_URL);
                    curl_easy_setopt(curl_put, CURLOPT_COOKIELIST, "FLUSH");
#ifdef _WIN32
                    curl_easy_setopt(curl_post, CURLOPT_COOKIEFILE, "D:\\data\\cookies.txt");
#else
                    curl_easy_setopt(curl_post, CURLOPT_COOKIEFILE, "/home/kmuscrc/PROJECT/DIVERSNS/COOKIES/cookies.txt");
#endif
                    break;
                }
                else {
                    printf("�������� �ʴ� ���̵��Դϴ�.\n");
                }

            }
            else if (strcmp(input, "2") == 0) {
                quit = 1;
                printf("�����մϴ�.\n");
                break;
            }
            else {
                printf("�� �� �� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
            }
        }

        if (quit) {
            break;
        }

        while (!quit) {//�����ͼۼ���
            printf("�����ϼ���.\n1.�α׾ƿ�\n2.�ø��� ������ ����\n3.���� ������ ���� ����\n4.����\n");
            scanf("%s", input);
            if (strcmp(input, "1") == 0) {
                printf("�α׾ƿ��մϴ�.\n");
                break;
            }
            else if (strcmp(input, "2") == 0) {
                printf("�����͸� �����մϴ�.\n");
                sprintf(acceleration, "0.2");
                sprintf(gaussMagnetic, "0.2");
                sprintf(angularRate, "0.2");
                sprintf(underwaterMicrophone, "0.2");
                sprintf(gesture, "0.2");
                sprintf(proximity, "0.2");
                sprintf(dryAmbientLight, "0.2");
                sprintf(dryAmbientRGB, "0.2");
                sprintf(dryBarometricPressure, "0.2");
                sprintf(dryTemperature, "0.2");
                sprintf(dryHumidity, "0.2");
                sprintf(underwaterPressure, "0.2");
                sprintf(underwaterTemperature, "0.2");
                sprintf(underwaterDepth, "0.2");
                sprintf(seaLevelAltitude, "0.2");
                sprintf(underwaterPictureLow, "0.2");
                sprintf(underwaterPictureHigh, "0.2");
                sprintf(underwaterVideoWithoutMic, "0.2");
                sprintf(underwaterVideoWithMic, "0.2");
                sprintf(gnss, "37.8847493, 127.1720248");

                sprintf(title, "title_test2");
                //sprintf(note, "ACCELEROMETER DATA: %s, GYROSCOPE DATA: %s, MAGETOMETER DATA: %s, UNDERWATER MICROPHONE: %s, GESTURE: %s, PROXIMITY: %s, DRY AMBIENT LIGHT: %s, DRY AMBIENT RGB: %s, DRY BAROMETIC PRESSURE: %s, DRY TEMPERATURE: %s, DRY HUMIDITY: %s, UNDERWATER PRESSURE: %s, UNDERWATER DEPTH: %s, ALTITUDE: %s, UNDERWATER TEMPERATURE: %s, UNDERWATER PICTURE(STILL SHOT) - LOW RESOLUTION: %s, UNDERWATER PICTURE(STILL SHOT) - HIGH RESOLUTION: %s, UNDERWATER VIDEO WITHOUT MICROPHONE: %s, UNDERWATER VIDEO WITH MICROPHONE: %s, GNSS: %s", acceleration, angularRate, gaussMagnetic, underwaterMicrophone, gesture, proximity, dryAmbientLight, dryAmbientRGB, dryBarometricPressure, dryTemperature, dryHumidity, underwaterPressure, underwaterDepth, seaLevelAltitude, underwaterTemperature, underwaterPictureLow, underwaterPictureHigh, underwaterVideoWithoutMic, underwaterVideoWithMic, gnss);
                sprintf(note, "Accelerometer Data: %s, Gyroscope Data: %s, Magetometer Data: %s, Underwater Microphone: %s, Gesture: %s, Proximity: %s, Dry Ambient Light: %s, Dry Ambient RGB: %s, Dry Barometic Pressure: %s, Dry Temperature: %s, Dry Humidity: %s, Underwater Pressure: %s, Underwater Depth: %s, Altitude: %s, Underwater Temperature: %s, Underwater Picture(Still Shot) - Low Resolution: %s, Underwater Picture(Still Shot) - High Resolution: %s, Underwater Video Without Microphone: %s, Underwater Video With Microphone: %s, GNSS: %s", acceleration, angularRate, gaussMagnetic, underwaterMicrophone, gesture, proximity, dryAmbientLight, dryAmbientRGB, dryBarometricPressure, dryTemperature, dryHumidity, underwaterPressure, underwaterDepth, seaLevelAltitude, underwaterTemperature, underwaterPictureLow, underwaterPictureHigh, underwaterVideoWithoutMic, underwaterVideoWithMic, gnss);
                sprintf(appendix, "appendix_test2");
                sprintf(vlc, "BLUE");
                sprintf(latitude, "37.8847493");
                sprintf(longitude, "127.1720248");
                //sprintf(postthis, "{\"authKey\": \"0\", \"type\": \"0\", \"title\": \"%s\", \"note\": \"%s\", \"appendix\": \"%s\", \"vlc\": \"%s\", \"latitude\": \"%s\", \"longitude\": \"%s\", \"accountType\": \"1\"}", title, note, appendix, vlc, latitude, longitude);
                sprintf(POST_URL, "http://www.uhsdm.site/v1/posts?authKey=0&type=0&title=%s&note=%s&appendix=%s&vlc=%s&latitude=%s&longitude=%s&accountType=1", title, curl_easy_escape(curl_put, note, strlen(note)), appendix, vlc, latitude, longitude);
                curl_easy_setopt(curl_post, CURLOPT_URL, POST_URL);
            }
            else if (strcmp(input, "3") == 0) {
                printf("������ �۽��մϴ�.\n");
                //curl_easy_setopt(curl_post, CURLOPT_POSTFIELDS, postthis);

                /* Perform the request, res will get the return code */
                res = curl_easy_perform(curl_post);
                /* Check for errors */
                if (res != CURLE_OK)
                    fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));

                //printf("ûũ : %s\n", chunk.memory);
                sprintf(chunk_temp, "%s", chunk.memory);
                temp = strtok(chunk_temp, " {}\":,");
                temp = strtok(NULL, " {}\":,");
                temp = strtok(NULL, " {}\":,");
                //printf("ûũ : %s\nûũ���� : %s\n���� : %s\n", chunk.memory, chunk_temp, temp);
                //gnum = atoi(chunk_temp);
                free(chunk.memory);
                chunk.memory = malloc(1);
                chunk.size = 0;
                if (strcmp(temp, "true") == 0) {
                    printf("������ ���ۿ� �����߽��ϴ�.\n");
                }
                else {
                    printf("������ ���ۿ� �����߽��ϴ�.\n");
                }

            }
            else if (strcmp(input, "4") == 0) {
                quit = 1;
                printf("�����մϴ�.\n");
                break;
            }
            else {
                printf("�� �� �� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
            }
        }

        if (quit) {
            break;
        }

    }
    //printf("��������1\n");
    /* always cleanup */
    curl_easy_cleanup(curl_put);
    //printf("��������2\n");
    free(chunk.memory);
    //printf("��������3\n");
    curl_easy_cleanup(curl_post);
    //printf("��������4\n");
    curl_slist_free_all(headerlist);
    //printf("��������5\n");
    return 0;
}