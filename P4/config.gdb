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

define p4
  set args p4_tests/$arg0.a -n
  run
end
