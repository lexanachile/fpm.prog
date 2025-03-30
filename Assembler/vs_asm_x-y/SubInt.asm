
.486
.model flat
.data
.code 
public _SubInt

	_SubInt proc
	push ebp
	mov ebp, esp
	mov eax, [ebp + 8]
	mov ebx, 1
	mul ebx
	sub eax, dword ptr[ebp + 12]
	pop ebp
	
	ret

_SubInt endp
end
