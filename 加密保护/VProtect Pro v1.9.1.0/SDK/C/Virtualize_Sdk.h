#pragma  once
//���ܣ���������ܿ�ʼ���
//��ע����Ҫ��Ͻ�����ǣ�VP_SDK_VIRTUALIZE_END��ʹ��
#define VP_SDK_VIRTUALIZE_BEGIN \
	__asm __emit 0xEB\
	__asm __emit 0x14\
	__asm __emit 0x56\
	__asm __emit 0x50\
	__asm __emit 0x5F\
	__asm __emit 0x56\
	__asm __emit 0x69\
	__asm __emit 0x72\
	__asm __emit 0x74\
	__asm __emit 0x75\
	__asm __emit 0x61\
	__asm __emit 0x6C\
	__asm __emit 0x69\
	__asm __emit 0x7A\
	__asm __emit 0x65\
	__asm __emit 0x5F\
	__asm __emit 0x42\
	__asm __emit 0x65\
	__asm __emit 0x67\
	__asm __emit 0x69\
	__asm __emit 0x6E\
	__asm __emit 0x00;
	
 //���ܣ���������ܽ������
//��ע����Ҫ��Ͽ�ʼ��ǣ�VP_SDK_VIRTUALIZE_BEGIN��ʹ��
#define VP_SDK_VIRTUALIZE_END \
	__asm __emit 0xEB\
	__asm __emit 0x12\
	__asm __emit 0x56\
	__asm __emit 0x50\
	__asm __emit 0x5F\
	__asm __emit 0x56\
	__asm __emit 0x69\
	__asm __emit 0x72\
	__asm __emit 0x74\
	__asm __emit 0x75\
	__asm __emit 0x61\
	__asm __emit 0x6C\
	__asm __emit 0x69\
	__asm __emit 0x7A\
	__asm __emit 0x65\
	__asm __emit 0x5F\
	__asm __emit 0x45\
	__asm __emit 0x6E\
	__asm __emit 0x64\
	__asm __emit 0x00;
	
 //���ܣ�������ܿ�ʼ���
//��ע����Ҫ��Ͻ�����ǣ�VP_SDK_MUTATION_END��ʹ��
#define VP_SDK_MUTATION_BEGIN \
	__asm __emit 0xEB\
	__asm __emit 0x12\
	__asm __emit 0x56\
	__asm __emit 0x50\
	__asm __emit 0x5F\
	__asm __emit 0x4D\
	__asm __emit 0x75\
	__asm __emit 0x74\
	__asm __emit 0x61\
	__asm __emit 0x74\
	__asm __emit 0x69\
	__asm __emit 0x6F\
	__asm __emit 0x6E\
	__asm __emit 0x5F\
	__asm __emit 0x42\
	__asm __emit 0x65\
	__asm __emit 0x67\
	__asm __emit 0x69\
	__asm __emit 0x6E\
	__asm __emit 0x00;
	
 //���ܣ�������ܽ������
//��ע����Ҫ��Ͽ�ʼ��ǣ�VP_SDK_MUTATION_BEGIN��ʹ��
#define VP_SDK_MUTATION_END \
	__asm __emit 0xEB\
	__asm __emit 0x10\
	__asm __emit 0x56\
	__asm __emit 0x50\
	__asm __emit 0x5F\
	__asm __emit 0x4D\
	__asm __emit 0x75\
	__asm __emit 0x74\
	__asm __emit 0x61\
	__asm __emit 0x74\
	__asm __emit 0x69\
	__asm __emit 0x6F\
	__asm __emit 0x6E\
	__asm __emit 0x5F\
	__asm __emit 0x45\
	__asm __emit 0x6E\
	__asm __emit 0x64\
	__asm __emit 0x00;
	
//���ܣ���������ܱ��
//��ע������Ҫ������ǣ�������Զ���λ������β
#define VP_SDK_VIRTUALIZE \
	__asm __emit 0xEB\
	__asm __emit 0x0B\
	__asm __emit 0x56\
	__asm __emit 0x69\
	__asm __emit 0x72\
	__asm __emit 0x74\
	__asm __emit 0x75\
	__asm __emit 0x61\
	__asm __emit 0x6C\
	__asm __emit 0x69\
	__asm __emit 0x7A\
	__asm __emit 0x65\
	__asm __emit 0x00;

//���ܣ������������ܱ��
//��ע������Ҫ������ǣ�������Զ���λ������β
#define VP_SDK_DEPTH_VIRTUALIZE \
	__asm __emit 0xEB\
	__asm __emit 0x11\
	__asm __emit 0x44\
	__asm __emit 0x65\
	__asm __emit 0x70\
	__asm __emit 0x74\
	__asm __emit 0x68\
	__asm __emit 0x5F\
	__asm __emit 0x56\
	__asm __emit 0x69\
	__asm __emit 0x72\
	__asm __emit 0x74\
	__asm __emit 0x75\
	__asm __emit 0x61\
	__asm __emit 0x6C\
	__asm __emit 0x69\
	__asm __emit 0x7A\
	__asm __emit 0x65\
	__asm __emit 0x00;

//���ܣ�������ܱ��
//��ע������Ҫ������ǣ�������Զ���λ������β
#define VP_SDK_MUTATION \
	__asm __emit 0xEB\
	__asm __emit 0x0C\
	__asm __emit 0x56\
	__asm __emit 0x50\
	__asm __emit 0x5F\
	__asm __emit 0x4D\
	__asm __emit 0x75\
	__asm __emit 0x74\
	__asm __emit 0x61\
	__asm __emit 0x74\
	__asm __emit 0x69\
	__asm __emit 0x6F\
	__asm __emit 0x6E\
	__asm __emit 0x00;

//���ܣ����������ܱ��
//��ע������Ҫ������ǣ�������Զ���λ������β	
#define VP_SDK_DEPTH_MUTATION \
	__asm __emit 0xEB\
	__asm __emit 0x12\
	__asm __emit 0x56\
	__asm __emit 0x50\
	__asm __emit 0x5F\
	__asm __emit 0x44\
	__asm __emit 0x65\
	__asm __emit 0x70\
	__asm __emit 0x74\
	__asm __emit 0x68\
	__asm __emit 0x5F\
	__asm __emit 0x4D\
	__asm __emit 0x75\
	__asm __emit 0x74\
	__asm __emit 0x61\
	__asm __emit 0x74\
	__asm __emit 0x69\
	__asm __emit 0x6F\
	__asm __emit 0x6E\
	__asm __emit 0x00;

//���ܣ�ע�������ܿ�ʼ���
//��ע����Ҫ��Ͻ�����ǣ�VP_SDK_REGDECODE_END��ʹ�ã�������Ҫʹ����Ȩϵͳ��
#define VP_SDK_REGDECODE_START \
	__asm __emit 0xEB\
	__asm __emit 0x15\
	__asm __emit 0x56\
	__asm __emit 0x50\
	__asm __emit 0x5F\
	__asm __emit 0x53\
	__asm __emit 0x44\
	__asm __emit 0x4B\
	__asm __emit 0x5F\
	__asm __emit 0x52\
	__asm __emit 0x45\
	__asm __emit 0x47\
	__asm __emit 0x44\
	__asm __emit 0x45\
	__asm __emit 0x43\
	__asm __emit 0x4F\
	__asm __emit 0x44\
	__asm __emit 0x45\
	__asm __emit 0x5F\
	__asm __emit 0x53\
	__asm __emit 0x54\
	__asm __emit 0x41\
	__asm __emit 0x00;

//���ܣ�ע�������ܽ������
//��ע����Ҫ��Ͽ�ʼ��ǣ�VP_SDK_REGDECODE_START��ʹ�ã�������Ҫʹ����Ȩϵͳ��
#define VP_SDK_REGDECODE_END \
	__asm __emit 0xEB\
	__asm __emit 0x15\
	__asm __emit 0x56\
	__asm __emit 0x50\
	__asm __emit 0x5F\
	__asm __emit 0x53\
	__asm __emit 0x44\
	__asm __emit 0x4B\
	__asm __emit 0x5F\
	__asm __emit 0x52\
	__asm __emit 0x45\
	__asm __emit 0x47\
	__asm __emit 0x44\
	__asm __emit 0x45\
	__asm __emit 0x43\
	__asm __emit 0x4F\
	__asm __emit 0x44\
	__asm __emit 0x45\
	__asm __emit 0x5F\
	__asm __emit 0x45\
	__asm __emit 0x4E\
	__asm __emit 0x44\
	__asm __emit 0x00;