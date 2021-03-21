#!/usr/bin/env python3

import sys

def acceptable(string):
	if string.startswith('#') or \
		string.startswith('-') or \
		string.startswith('null') or \
		string.startswith('BUILTIN'):
		return False
	else:
		return True

def get_syscall_names(string):
	syscall_list = []
	s = string.rpartition(':')
	if ':' == s[1]:
		seq = s[0].split(', ')
		for syscall in seq:
			parts = syscall.rpartition('/')
			if parts[1] == '/':
				syscall_list.append(parts[0])
			else:
				syscall_list.append(parts[2])
	return syscall_list

syscall_list = []
with open(sys.argv[1]) as f:
	for line in f:
		if acceptable(line):
			syscall_list += get_syscall_names(line)

print('''#ifndef __VU_SYSCALL_NO__
#define __VU_SYSCALL_NO__

#include <sys/syscall.h>

''')

syscall_number = -4096
for syscall in syscall_list:
	syscall_def = '__NR_' + syscall
	print('''#ifndef {0}
#	define POSTDEF{0}
#	define {0}	{1}
#endif\n'''.format(syscall_def, syscall_number))
	syscall_number -= 1

print('\n\n#endif')