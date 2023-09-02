open! StdLabels
open! MoreLabels

let is_teacher_free_buses classes =
  let total_students = List.fold_left classes ~init:0 ~f:( + ) in
  match total_students mod 3 with
  | 1 | 2 -> "-1\n"
  | 0 ->
    let bus_size = total_students / 3 in
    let splits = Array.make 2 bus_size in
    let is_three_buses =
      List.mapi classes ~f:(fun i students -> i, students)
      |> List.fold_left ~init:(0, 0) ~f:(fun (count, bus) (i, students) ->
        match bus + students with
        | x when x > bus_size ->
          if count < 2 then splits.(count) <- i - 1;
          count + 1, students
        | x when x = bus_size ->
          if count < 2 then splits.(count) <- i;
          count + 1, 0
        | x -> count, x)
      |> fst
      |> Int.equal 3
    in
    (match is_three_buses, splits.(0), splits.(1) with
     | false, _, _ | true, -1, _ -> "-1\n"
     | true, a, b -> Printf.sprintf "%d %d\n" (a + 1) (b + 1))
  | _ -> assert false
;;

let () =
  let _ = input_line stdin in
  input_line stdin
  |> String.split_on_char ~sep:' '
  |> List.map ~f:int_of_string
  |> is_teacher_free_buses
  |> output_string stdout
;;
