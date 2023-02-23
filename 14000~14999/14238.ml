open! StdLabels
open! MoreLabels

let init_schedule dp =
  let rec loop x y =
    if x = 3 then ()
    else if y = 3 then loop (x + 1) 0
    else (
      dp.(x).(y) <- Some "";
      loop x (y + 1))
  in
  loop 0 0

let valid_scehdule a b c =
  let dp =
    Array.init (a + 1) ~f:(fun _ ->
        Array.init (b + 1) ~f:(fun _ ->
            Array.init (c + 1) ~f:(fun _ ->
                Array.init 3 ~f:(fun _ -> Array.init 3 ~f:(fun _ -> None)))))
  in

  init_schedule dp.(0).(0).(0);

  let rec loop x y z p q =
    if x = a + 1 then ()
    else if y = b + 1 then loop (x + 1) 0 z p q
    else if z = c + 1 then loop x (y + 1) 0 p q
    else if p = 3 then loop x y (z + 1) 0 q
    else if q = 3 then loop x y z (p + 1) 0
    else
      match dp.(x).(y).(z).(p).(q) with
      | None -> loop x y z p (q + 1)
      | Some s ->
          (* Add a *)
          if x < a then dp.(x + 1).(y).(z).(q).(0) <- Some (s ^ "A");

          (* Add b *)
          if y < b && q <> 1 then dp.(x).(y + 1).(z).(q).(1) <- Some (s ^ "B");

          (* Add c *)
          if z < c && p <> 2 && q <> 2 then
            dp.(x).(y).(z + 1).(p).(2) <- Some (s ^ "C");

          loop x y z p (q + 1)
  in

  loop 0 0 0 0 0;

  let find_some dp =
    let rec loop x y =
      if x = 3 then None
      else if y = 3 then loop (x + 1) 0
      else match dp.(x).(y) with Some s -> Some s | None -> loop x (y + 1)
    in
    loop 0 0
  in

  find_some dp.(a).(b).(c)

let () =
  let a, b, c =
    input_line stdin |> String.to_seq
    |> Seq.fold_left
         (fun (a, b, c) ch ->
           match ch with
           | 'A' -> (a + 1, b, c)
           | 'B' -> (a, b + 1, c)
           | 'C' -> (a, b, c + 1)
           | _ -> assert false)
         (0, 0, 0)
  in

  match valid_scehdule a b c with
  | None -> output_string stdout "-1\n"
  | Some s -> output_string stdout (s ^ "\n")
