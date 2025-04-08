set breakpoint pending on
set confirm off
file ./ac
break a_lang::Err::report
commands
	where
end
break a_lang::InternalError::InternalError
commands
	where
end

define p3
  set args p3_tests/$arg0.dm -p --
  run
end
