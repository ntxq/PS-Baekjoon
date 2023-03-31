open! StdLabels
open! MoreLabels

let base_of_char x =
  if x <= 9 then Char.chr (Char.code '0' + x)
  else Char.chr (Char.code 'A' + x - 10)

let () =
  Scanf.scanf "%d %d" (fun n b ->
      let rec loop i =
        if i < b then [ base_of_char i ]
        else
          let q, r = (i / b, i mod b) in
          base_of_char r :: loop q
      in
      loop n |> List.rev |> List.iter ~f:print_char)
