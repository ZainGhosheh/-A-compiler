set breakpoint pending on
set startup-quietly on
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
break a_lang::ToDoError::ToDoError
commands
	where
end

define p6
  set args p6_tests/$arg0.a -a --
  run
end
