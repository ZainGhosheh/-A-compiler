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

define t1
  set args p1_tests/$arg0.a -o --
  run
end
