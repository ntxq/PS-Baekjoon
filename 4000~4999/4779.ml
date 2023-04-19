open! StdLabels
open! MoreLabels

let cantor_len len =
  let rec loop len acc = if len = 0 then acc else loop (len - 1) (acc * 3) in
  loop len 1

let rec print_cantor len =
  if len = 1 then print_char '-'
  else (
    print_cantor (len / 3);
    String.make (len / 3) ' ' |> print_string;
    print_cantor (len / 3))

let () =
  let rec loop () =
    match read_line () with
    | n ->
        cantor_len (int_of_string n) |> print_cantor;
        print_newline ();
        loop ()
    | exception End_of_file -> ()
  in
  loop ()
