function getFirstNumber(s)
  character(128) s
  i = 1
  getFirstNumber = 200
  do while(i .lt. 128)
  	if(s(i:i) .eq. '1') then
  	  getFirstNumber = i
  	  exit
  	else if(s(i:i) .eq. '2') then
  	  getFirstNumber = i
  	  exit  	
  	else if(s(i:i) .eq. '3') then
  	  getFirstNumber = i
  	  exit  	
  	else if(s(i:i) .eq. '4') then
  	  getFirstNumber = i
  	  exit  	
  	else if(s(i:i) .eq. '5') then
  	  getFirstNumber = i
  	  exit  	
  	else if(s(i:i) .eq. '6') then
  	  getFirstNumber = i
  	  exit  	
  	else if(s(i:i) .eq. '7') then
  	  getFirstNumber = i
  	  exit  	
  	else if(s(i:i) .eq. '8') then
  	  getFirstNumber = i
  	  exit  	
  	else if(s(i:i) .eq. '9') then
  	  getFirstNumber = i
  	  exit  	
  	endif
  	i = i + 1
  enddo  
end function getFirstNumber

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

function getLastNumber(s)
  character(128) s
  i = 1
  getLastNumber = 200
  do while(i .lt. 128)
  	if(s(i:i) .eq. '1') then
  	  getLastNumber = i
  	else if(s(i:i) .eq. '2') then
  	  getLastNumber = i
  	else if(s(i:i) .eq. '3') then
  	  getLastNumber = i
  	else if(s(i:i) .eq. '4') then
  	  getLastNumber = i
  	else if(s(i:i) .eq. '5') then
  	  getLastNumber = i
  	else if(s(i:i) .eq. '6') then
  	  getLastNumber = i
  	else if(s(i:i) .eq. '7') then
  	  getLastNumber = i
  	else if(s(i:i) .eq. '8') then
  	  getLastNumber = i
  	else if(s(i:i) .eq. '9') then
  	  getLastNumber = i
  	endif
  	i = i + 1
  enddo  
end function getLastNumber

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

program AOC2023Day1

character(128) buf
integer*8 answer1
answer1 = 0

open(1, file = 'input.txt')
do
  read(1, '(a)', iostat = io) buf
  if(io /= 0) exit 
  i1 = getFirstNumber(buf)
  i2 = getLastNumber(buf)
  ival = (ichar(buf(i1:i1)) - 48) * 10
  ival = ival + (ichar(buf(i2:i2)) - 48)
  answer1 = answer1 + ival
enddo

close(1)
print *, 'PART1 answer = ', answer1
end program AOC2023Day1
