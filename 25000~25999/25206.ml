open! StdLabels
open! MoreLabels

let () =
  let rec loop acc1 acc2 =
    match input_line stdin with
    | exception End_of_file -> acc2 /. acc1
    | line ->
        Scanf.sscanf line " %s %f %s" (fun _ credit grade ->
            match grade with
            | "A+" -> loop (acc1 +. credit) (acc2 +. (credit *. 4.5))
            | "A0" -> loop (acc1 +. credit) (acc2 +. (credit *. 4.0))
            | "B+" -> loop (acc1 +. credit) (acc2 +. (credit *. 3.5))
            | "B0" -> loop (acc1 +. credit) (acc2 +. (credit *. 3.0))
            | "C+" -> loop (acc1 +. credit) (acc2 +. (credit *. 2.5))
            | "C0" -> loop (acc1 +. credit) (acc2 +. (credit *. 2.0))
            | "D+" -> loop (acc1 +. credit) (acc2 +. (credit *. 1.5))
            | "D0" -> loop (acc1 +. credit) (acc2 +. (credit *. 1.0))
            | "F" -> loop (acc1 +. credit) (acc2 +. (credit *. 0.0))
            | _ -> loop acc1 acc2)
  in
  Printf.printf "%.5f" (loop 0.0 0.0)
