#ifndef _XML_COM_H_
#define _XML_COM_H_

#define XML_MAX_MACRO_CHAR_NUM  128
#define XML_MAX_FILE_LINE_LEN   1024
#define XML_MAX_KEY_LEN         64

enum XmlErr{
	Xml_Succeed = 0,
	err_file_open_failed = 10000,
	err_memory_exception,
	err_param_not_valid,
	err_file_del_comment_failed,
	err_file_del_brace_failed,
	err_file_del_key_and_func_failed,
	err_pick_enum_from_file_failed,
	err_pick_struct_from_file_failed,
	err_make_type_ex_file_failed,
	err_make_struct_cpp_file_failed,
	err_enum_format_invalid,
	err_struct_format_invalid,
};

#endif //_XML_COM_H_