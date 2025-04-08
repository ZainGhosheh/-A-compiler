set breakpoint pending on
set confirm off
file ./ac
break a_lang::Err::report
commands
	where
end
break a_lang::ToDoError::ToDoError
commands
	where
end
break a_lang::InternalError::InternalError
commands
	where
end

define t7
  set args p7_tests/$arg0.ac -o --
  run
end
