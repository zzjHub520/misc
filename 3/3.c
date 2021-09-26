#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <netinet/ether.h>  
  
int main(int argc,char *argv[])  
{  
    int i = 0;  
    unsigned char buf[1024] = "";  
    // 当类型为SOCK_RAW时，发送的时候需要给自己加上一个MAC头部
    int sock_raw_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));  
    while(1)  
    {  
         char src_mac[18] = "";  
         char dst_mac[18] = "";  
        //获取链路层的数据帧  
        recvfrom(sock_raw_fd, buf, sizeof(buf),0,NULL,NULL);  
        //从buf里提取目的mac、源mac，填充以太网数据帧的目的MAC地址和源MAC地址  
        sprintf(dst_mac,"%02x:%02x:%02x:%02x:%02x:%02x", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);  
        sprintf(src_mac,"%02x:%02x:%02x:%02x:%02x:%02x", buf[6], buf[7], buf[8], buf[9], buf[10], buf[11]);  
        //判断是否为IP数据包  
        if(buf[12]==0x08 && buf[13]==0x00)  
        {     
            //为了防止IP过多，先把这两行屏蔽
            //printf("______________IP PACKAGE_______________\n");  
            //printf("MAC:%s >> %s\n",src_mac,dst_mac);  
        }
        else  
            if(buf[12]==0x08 && buf[13]==0x06)  //判断是否为ARP数据包  
        {  
            printf("______________ARP PACKAGE_______________\n");  
            printf("MAC:%s >> %s\n",src_mac,dst_mac);  
        }//判断是否为RARP数据包  
        else if(buf[12]==0x80 && buf[13]==0x35)  
        {  
            printf("______________RARP PACKAGE_______________\n");  
            printf("MAC:%s>>%s\n",src_mac,dst_mac);  
        }   
    }  
    return 0;  
}