open! Core
(* open! StdLabels
   open! MoreLabels *)

let find_meow_factor s =
  let meow_regex = Re.Posix.re "(meow)" |> Re.compile in
  let one_regex =
    Re.Posix.re "((eow|mow|mew|meo)|(me.ow)|(m.ow|me.w)|(moew))" |> Re.compile
  in
  let two_regex =
    Re.Posix.re "((me|mo|mw|eo|ew|ow)|(m.o|e.w|m..w)|(em.w|m.wo))" |> Re.compile
  in
  let three_regex = Re.Posix.re "(m|e|o|w)" |> Re.compile in
  if Re.execp meow_regex s
  then 0
  else if Re.execp one_regex s
  then 1
  else if Re.execp two_regex s
  then 2
  else if Re.execp three_regex s
  then 3
  else 4
;;

let () =
  let s = In_channel.input_line_exn In_channel.stdin in
  find_meow_factor s |> string_of_int |> Out_channel.output_string Out_channel.stdout;
  Out_channel.output_char Out_channel.stdout '\n'
;;
