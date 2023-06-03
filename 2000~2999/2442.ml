open! StdLabels
open! MoreLabels

let star_row cur_h max_h =
  let pad = max_h - cur_h in
  let stars = (2 * cur_h) - 1 in
  String.concat ~sep:"" [ String.make pad ' '; String.make stars '*' ]

let star_tree h =
  List.fold_right ~init:[]
    ~f:(fun cur_h acc -> star_row cur_h h :: acc)
    (List.init ~len:h ~f:(fun i -> i + 1))
  |> String.concat ~sep:"\n"

let () = Scanf.scanf "%d" (fun h -> print_endline (star_tree h))
