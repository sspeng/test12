program hello

interface
   subroutine marker1begin() bind(c,name='marker1begin')
     use, intrinsic :: iso_c_binding
   end subroutine marker1begin

   subroutine marker1end() bind(c,name='marker1end')
     use, intrinsic :: iso_c_binding
   end subroutine marker1end

   subroutine finalizeCallLogging() bind(c,name='finalizeCallLogging')
     use, intrinsic :: iso_c_binding
   end subroutine finalizeCallLogging
end interface

integer(kind=8) :: n, a, b, c

  call marker1begin
  do n=1,300000000
     a = b/c;
  end do
  call marker1end

  call finalizeCallLogging

end program hello
